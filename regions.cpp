#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  cv::Mat image;
  cv::Vec3b val;

  int p1x, p1y, p2x, p2y;

  image= cv::imread(argv[1],cv::IMREAD_GRAYSCALE);
  if(!image.data)
    std::cout << "nao abriu a imagem "<< std::endl;

  cv::namedWindow("janela", cv::WINDOW_AUTOSIZE);

  std::cout << "entre com os dois pontos dentro do limite (" << image.rows << "," << image.cols << "): \n";
  std::cin >> p1x >> p1y >> p2x >> p2y;

  cv::imshow("janela", image);  
  cv::waitKey();
  
  if(p1y>=0 && p2y<=image.cols && p1x>=0 && p2x<=image.rows){
    for(int i=p1y;i<p2y;i++){
      for(int j=p1x;j<p2x;j++){
        image.at<uchar>(i,j)= 255 - image.at<uchar>(i,j);
      }
    }

    cv::imshow("janela", image);  
    cv::waitKey();
  }
  else{
    cout << "pontos fora do limite " << std::endl;
  }

  return 0;
}
