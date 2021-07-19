#include <iostream>
#include <cstdio>
#include <opencv2/opencv.hpp>

int width, height;

int top_slider = 0;
int top_slider_max = 100;
int vertical_position = 0;

int height_slider = 0;
int height_slider_max = 100;
int band_size = 0;

int weight_slider = 0;
int weight_slider_max = 100;
double ponderation = 0;

cv::Mat image1, image2, alfa1, alfa2;
cv::VideoWriter captured;

char TrackbarName[50];

void update(){
    cv::Mat originalImage, blurImage, finalImage;
    image1.convertTo(originalImage, CV_32FC3);
    image2.convertTo(blurImage, CV_32FC3);
    multiply(originalImage, alfa1, originalImage);
    multiply(blurImage, alfa2, blurImage);
    add(originalImage, blurImage, finalImage);
    finalImage.convertTo(finalImage, CV_8UC3);
    imshow("tiltshift", finalImage);
    captured.write(finalImage);
}

void blur(int blurValue){
    cv::Mat aux, mask;
    float media[] = {1,1,1,
                     1,1,1,
                     1,1,1};

    mask = cv::Mat(3, 3, CV_32F, media); 
    scaleAdd(mask, 1/9.0, cv::Mat::zeros(3,3,CV_32F), mask);
    image1.convertTo(aux, CV_32F); 
    for (int i = 0; i < blurValue; i++) {
        filter2D(aux, aux, aux.depth(), mask, cv::Point(1, 1), 0);
    }
    aux=abs(aux);
    aux.convertTo(image2, CV_8UC3);
}

void tiltShift() {
    int l1 = -band_size/2;
    int l2 = -l1;

    alfa1 = cv::Mat::zeros(image1.rows, image1.cols, CV_32F);
    alfa2 = cv::Mat::zeros(image1.rows, image1.cols, CV_32F);
    int i, j;
    for (i = 0; i < alfa1.rows; i++) {
        int x = i - (vertical_position + band_size/2);
        float alfa = 0.5f * (tanh((x - l1)/ponderation) 
                                    - tanh((x - l2)/ponderation));
        for (j = 0; j < alfa1.cols; j++) {
            alfa1.at<float>(i, j) = alfa;
            alfa2.at<float>(i, j) = 1 - alfa;
        }
    }
    cv::Mat A1[] = {alfa1, alfa1, alfa1};
    cv::Mat A2[] = {alfa2, alfa2, alfa2};
    merge(A1, 3, alfa1);
    merge(A2, 3, alfa2);
    update();
}

void on_trackbar_posicaoVertical(int, void*){
    vertical_position = top_slider*height/top_slider_max;
    tiltShift();
}

void on_trackbar_alturaRegiao(int, void*) {
    band_size = height_slider*height/height_slider_max;
    if (band_size == 0) {
        band_size = 1;
    }

    if (band_size > height) {
        band_size = height;
    }
    tiltShift();
}

void on_trackbar_forcaDecaimento(int, void*){
    ponderation = (double) weight_slider;
    if (ponderation < 1) {
        ponderation = 1;
    }
    tiltShift();
}

int main(int argvc, char** argv){
  cv::VideoCapture video;
  video.open(argv[1]);

  width = video.get(cv::CAP_PROP_FRAME_WIDTH);
  height = video.get(cv::CAP_PROP_FRAME_HEIGHT);

  captured.open("tiltshiftvideo.avi", cv::VideoWriter::fourcc('M','J','P','G'),
                           10, cv::Size(width,height));

  cv::namedWindow("tiltshift", 1);
  
  std::sprintf( TrackbarName, "Posicao verical");
  cv::createTrackbar( TrackbarName, "tiltshift",
                      &top_slider,
                      top_slider_max,
                      on_trackbar_posicaoVertical );
  std::sprintf( TrackbarName, "Altura da região");
  cv::createTrackbar( TrackbarName, "tiltshift",
                    &height_slider,
                    height_slider_max,
                    on_trackbar_alturaRegiao);
  std::sprintf( TrackbarName, "Forca decaimento");
  cv::createTrackbar( TrackbarName, "tiltshift",
                    &weight_slider,
                    weight_slider_max,
                    on_trackbar_forcaDecaimento);

  int frame = 0;
  cv::Mat discardFrame;
    while(1){
        video >> discardFrame;

        if (discardFrame.empty()){
            video.release();
            video.open(argv[1]);
            frame = 0;
            continue;
        }

        frame++;

        if(frame%2 != 0){
            image1 = discardFrame.clone();
            image2 = image1.clone();

            blur(10);
            tiltShift();
        }

        char key = (char)cv::waitKey(30);
        if (key == 27) break;
    }

    video.release();
    captured.release();

    cv::destroyAllWindows();
    return 0;
}
