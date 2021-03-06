#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void deslocaDFT(Mat& image ){
  Mat tmp, A, B, C, D;
  image = image(Rect(0, 0, image.cols & -2, image.rows & -2));
  int cx = image.cols/2;
  int cy = image.rows/2;
  A = image(Rect(0, 0, cx, cy));
  B = image(Rect(cx, 0, cx, cy));
  C = image(Rect(0, cy, cx, cy));
  D = image(Rect(cx, cy, cx, cy));
  A.copyTo(tmp);
  D.copyTo(A);  
  tmp.copyTo(D);
  C.copyTo(tmp);  
  B.copyTo(C);  
  tmp.copyTo(B);
}

int gammaL_slider = 5, gammaH_slider = 20, sharpC_slider = 4, cutoff_slider = 30;
const int gammaL_max = 10, gammaH_max = 40, sharpC_max = 15, cutoff_max = 120;
double gammaL, gammaH, sharpC, cutoff;
Mat image, imageFiltered, padded;
int dft_M, dft_N;

Mat homomorphic(double gl, double gh, double c, double d0){
  Mat filter = Mat(padded.size(), CV_32FC2, Scalar(0));
  Mat tmp = Mat(dft_M, dft_N, CV_32F);
  
  for(int i=0; i<dft_M; i++){
    for(int j=0; j<dft_N; j++){
      tmp.at<float> (i,j) = (gh - gl)*(1 - exp(-c*(((i-dft_M/2)*(i-dft_M/2) + 
      (j-dft_N/2)*(j-dft_N/2) ) / (d0*d0)))) + gl;
    }
  }

  Mat comps[]= {tmp,tmp};
  imshow("Filter", tmp);
  merge(comps, 2, filter);
  return filter;
}

void applyFilter(void){
  Mat complex;
  vector<Mat> planos; planos.clear();
  Mat zeros = Mat_<float>::zeros(padded.size());
  Mat realInput = Mat_<float>(padded);
  
  realInput += Scalar::all(1);
  log(realInput,realInput);
  planos.push_back(realInput);
  planos.push_back(zeros);
  merge(planos, complex);

  dft(complex, complex);
  deslocaDFT(complex);
  resize(complex,complex,padded.size());
  normalize(complex,complex,0,1,cv::NORM_MINMAX);

  Mat filter = homomorphic(gammaL,gammaH,sharpC,cutoff);

  mulSpectrums(complex,filter,complex,0);
  deslocaDFT(complex);
  idft(complex, complex);

  planos.clear();
  split(complex, planos);
  exp(planos[0],planos[0]);
  normalize(planos[0], planos[0], 0, 1, cv::NORM_MINMAX);
  imageFiltered = planos[0].clone();
}

void on_trackbar(int, void*){
  gammaL = (double) gammaL_slider/10.0;
  gammaH = (double) gammaH_slider/10.0;
  sharpC = (double) sharpC_slider;
  cutoff = (double) cutoff_slider;
  applyFilter();
  imshow("Homomorphic",imageFiltered);
}

int main(int argc, char** argv){
  if(argc < 2) {
    cout <<  "Necessita de uma imagem como segundo argumento!\n";
    return -1;
  }

  image = imread(argv[1], IMREAD_GRAYSCALE);

  if(!image.data) {
    cout<<"Erro ao abrir a imagem!\n";
    return -1;
  }

  namedWindow("Homomorphic", WINDOW_KEEPRATIO);
  namedWindow("Original", WINDOW_KEEPRATIO);
  namedWindow("Filter", WINDOW_KEEPRATIO);

  imshow("Original",image);

  dft_M = getOptimalDFTSize(image.rows);
  dft_N = getOptimalDFTSize(image.cols);

  copyMakeBorder(image, padded, 0, dft_M - image.rows, 0, dft_N - image.cols, 
  BORDER_CONSTANT, Scalar::all(0));
 
  imageFiltered = padded.clone();

  cout << "Original: " << image.rows << "x" << image.cols << endl;
  cout << "Padded: "   << padded.rows << "x" << padded.cols << endl;

  char TrackbarName[50];

  sprintf( TrackbarName, "Gamma L");
  createTrackbar( TrackbarName, "Homomorphic", &gammaL_slider, gammaL_max, on_trackbar);

  sprintf( TrackbarName, "Gamma H");
  createTrackbar( TrackbarName, "Homomorphic", &gammaH_slider, gammaH_max, on_trackbar);

  sprintf( TrackbarName, "Sharp C");
  createTrackbar( TrackbarName, "Homomorphic", &sharpC_slider, sharpC_max, on_trackbar);
  
  sprintf( TrackbarName, "Cutoff Freq");
  createTrackbar( TrackbarName, "Homomorphic", &cutoff_slider, cutoff_max, on_trackbar);

  waitKey(0);
  return 0;
}