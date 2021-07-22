#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv){
  cv::Mat image, imageEq;
  int width, height;
  cv::VideoCapture cap;
  cv::Mat hist, histEq;

  int nbins = 128;
  float range[] = {0, 255};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;
  int key;

  cap.open(0);
  
  if(!cap.isOpened()){
    std::cout << "cameras indisponiveis";
    return -1;
  }
  
  cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);  
  width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
  height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

  std::cout << "largura = " << width << std::endl;
  std::cout << "altura  = " << height << std::endl;

  while(1){
    cap >> image;
    cv::cvtColor(image, image, cv::COLOR_RGB2GRAY);
    cv::flip(image,image,1);
    cv::equalizeHist(image, imageEq);

    cv::calcHist(&image, 1, 0, cv::Mat(), hist, 1,
                 &nbins, &histrange,
                 uniform, acummulate);
    cv::calcHist(&imageEq, 1, 0, cv::Mat(), histEq, 1,
                 &nbins, &histrange,
                 uniform, acummulate);

    int histw = nbins, histh = nbins/2;
    cv::Mat histIm(histh, histw, CV_8UC1, cv::Scalar(0,0,0));
    cv::Mat histImEq(histh, histw, CV_8UC1, cv::Scalar(0,0,0));
    
    cv::normalize(hist, hist, 0, histIm.rows, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(histEq, histEq, 0, histImEq.rows, cv::NORM_MINMAX, -1, cv::Mat());
    
    for(int i=0; i<nbins; i++){
      cv::line(histIm,
               cv::Point(i, histh),
               cv::Point(i, histh-cvRound(hist.at<float>(i))),
               cv::Scalar(255, 255, 255), 1, 8, 0);
      cv::line(histImEq,
               cv::Point(i, histh),
               cv::Point(i, histh-cvRound(histEq.at<float>(i))),
               cv::Scalar(255, 255, 255), 1, 8, 0);
    }
    histIm.copyTo(image(cv::Rect(0, 0       ,nbins, histh)));
    histImEq.copyTo(image(cv::Rect(0, histh   ,nbins, histh)));
    cv::imshow("image", image);
    key = cv::waitKey(30);
    if(key == 27) break;
  }
  cv::imwrite("equalizesaida.png",image);
  return 0;
}
