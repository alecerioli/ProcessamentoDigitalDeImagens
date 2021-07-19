#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Mat image, A, B, C, D, AB, CD;
    Rect rect;

    image = imread(argv[1], cv::IMREAD_GRAYSCALE);
    if (!image.data)
    {
        cout << "nao abriu a imagem" << endl;
        return -1;
    }
    namedWindow("janela", cv::WINDOW_AUTOSIZE);

    imshow("janela", image);
    waitKey();

    rect = Rect(Point(0, 0), Point(image.rows / 2, image.cols / 2));
    A = Mat(image, rect);
    rect = Rect(Point(0, image.cols / 2), Point(image.rows / 2, image.cols));
    B = Mat(image, rect);
    rect = Rect(Point(image.rows / 2, 0), Point(image.rows, image.cols / 2));
    C = Mat(image, rect);
    rect = Rect(Point(image.rows / 2, image.cols / 2), Point(image.rows, image.cols));
    D = Mat(image, rect);

    vconcat(D, C, CD);
    vconcat(B, A, AB);
    hconcat(CD, AB, image);

    imshow("janela", image);
    waitKey();

    return 0;
}
