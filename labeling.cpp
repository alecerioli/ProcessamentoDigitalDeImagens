#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv){
  cv::Mat image, realce;
  int width, height;
  int nobjects, nburacos;

  cv::Point p;
  image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
  
  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }

  width=image.cols;
  height=image.rows;
  nobjects = nburacos = 0;
  p.x=0;
  p.y=0;

  cv::imshow("image", image);
  cv::waitKey();
  
  //verifica bordas verticais
  for (int j = 0; j < width; j++){
    if (image.at<uchar>(0, j) == 255){
      p.x = j;
      p.y = 0;
      floodFill(image, p, 0);
    }
    if (image.at<uchar>(height - 1, j) == 255){
      p.x = j;
      p.y = height - 1;
      floodFill(image, p, 0);
    }
  }
  //verifica bordas horizontais
  for (int i = 0; i < height; i++){
    if (image.at<uchar>(i, 0) == 255){
      p.x = 0;
      p.y = i;
      floodFill(image, p, 0);
    }
    if (image.at<uchar>(i, width - 1) == 255){
      p.x = width - 1;
      p.y = i;
      floodFill(image, p, 0);
    }
  }

  cv::imshow("image", image);
  cv::imwrite("labelingsemborda.png", image);
  cv::waitKey();
  
  p.x = 0;
  p.y = 0;
  floodFill(image, p, 120);
  imshow("image", image);
  cv::imwrite("labelingcinza.png", image);
  waitKey();
  
  for (int i = 0; i < height; i++){
    for (int j = 0; j < width; j++){
      if (image.at<uchar>(i, j) == 0){
        if (image.at<uchar>(i, j - 1) == 255){
          nburacos++;
          p.x = j - 1;
          p.y = i;
          floodFill(image, p, 120);
        }
        p.x = j;
        p.y = i;
        floodFill(image, p, 120);
      }
    }
  }
  imshow("image", image);
  cv::imwrite("labelingsemburacos.png", image);
  waitKey();

  // encontrando regioes
  for (int i = 1; i < height; i++){
    for (int j = 1; j < width; j++){
      if (image.at<uchar>(i, j) == 255){
        nobjects++;
        p.x = j;
        p.y = i;
        floodFill(image, p, nobjects);
      }
    }
  }
  imshow("image", image);
  cv::imwrite("labelingfinal.png", image);
  std::cout << "a figura tem " << nobjects + nburacos << " bolhas, sendo " 
  << nobjects << " sem buracos e " << nburacos << " com buracos" << std::endl;
  waitKey();

  return 0;
}
