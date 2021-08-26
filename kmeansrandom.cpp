#include <opencv2/opencv.hpp>
#include <cstdlib>

using namespace cv;
using namespace std;

int main( int argc, char** argv ){
  int nClusters = 8;
  Mat *rotulos, *centros;
  int nRodadas = 1;
  
  Mat img = imread( argv[1], IMREAD_COLOR);
  Mat samples(img.rows * img.cols, 3, CV_32F);

  for( int y = 0; y < img.rows; y++ ){
    for( int x = 0; x < img.cols; x++ ){
      for( int z = 0; z < 3; z++){
        samples.at<float>(y + x*img.rows, z) = img.at<Vec3b>(y,x)[z];
	    }
	  }
  }

  rotulos = new Mat[10];
  centros = new Mat[10];

  for(int i=0;i<10;i++){
    kmeans(samples,
		 nClusters,
		 rotulos[i],
		 TermCriteria(cv::TermCriteria::MAX_ITER|cv::TermCriteria::EPS, 10000, 0.0001),
		 nRodadas,
		 KMEANS_RANDOM_CENTERS,
		 centros[i]);

     Mat rotulada( img.size(), img.type() );

     for( int y = 0; y < img.rows; y++ ){
        for( int x = 0; x < img.cols; x++ ){ 
	        int indice = rotulos[i].at<int>(y + x*img.rows,0);
	        rotulada.at<Vec3b>(y,x)[0] = (uchar) centros[i].at<float>(indice, 0);
	        rotulada.at<Vec3b>(y,x)[1] = (uchar) centros[i].at<float>(indice, 1);
	        rotulada.at<Vec3b>(y,x)[2] = (uchar) centros[i].at<float>(indice, 2);
        }
     }
     char save[50];
     sprintf(save, "saidakmeans%d.jpg", i);
     string s(save);
     imwrite(s, rotulada);
  }

  waitKey( 0 );
}
