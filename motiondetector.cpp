#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv){
  cv::Mat image;
  int width, height;
  cv::VideoCapture cap;
  cv::Mat histAtual, histPassado;

  double limite = 10;
  int nbins = 64;
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

  cap >> image;
  cv::cvtColor(image, image, cv::COLOR_RGB2GRAY);

  cv::calcHist(&image, 1, 0, cv::Mat(), histPassado, 1,
                 &nbins, &histrange,
                 uniform, acummulate);
  cv::normalize(histPassado, histPassado, 0, histPassado.rows, cv::NORM_MINMAX, -1, cv::Mat());

  while(1){
    cap >> image;
    cv::cvtColor(image, image, cv::COLOR_RGB2GRAY);

    cv::calcHist(&image, 1, 0, cv::Mat(), histAtual, 1,
                 &nbins, &histrange,
                 uniform, acummulate);

    cv::normalize(histAtual, histAtual, 0, histAtual.rows, cv::NORM_MINMAX, -1, cv::Mat());

    double diferenca = compareHist(histAtual, histPassado, 1);

    if((diferenca > limite) && (diferenca < 1000)){
        cv::Mat branco(height, width, CV_8UC1, 255);
        branco.copyTo(image(cv::Rect(0,0,width,height)));
        std::cout << "Movimento detectado\n" << diferenca << std::endl;
    }
    
    histAtual.copyTo(histPassado);

    cv::imshow("image", image);
    key = cv::waitKey(30);
    if(key == 27) break;
  }
  return 0;
}
