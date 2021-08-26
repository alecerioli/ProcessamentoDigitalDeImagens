#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int canny_slider = 15;
int canny_slider_max = 200;

char TrackbarName[50];

Mat image, edges, bestEdges, points;

void getPointillisticImage() {
    int height = image.size().height, width = image.size().width;

    points = Mat(height, width, CV_8UC3, Scalar(255, 255, 255));

    Canny(image, edges, canny_slider, 3 * canny_slider);
    Canny(image, bestEdges, 2 * canny_slider, 6 * canny_slider);

    vector<vector<int>> edgesCoordinates, restCoordentate, bestEdgesCoordinates;

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(edges.at<uchar>(i, j) == 255) {
                edgesCoordinates.push_back({i, j});
            }
            if(bestEdges.at<uchar>(i,j) == 255){
                bestEdgesCoordinates.push_back({i,j});
            }
            restCoordentate.push_back({i, j});
        }
    }

    random_shuffle(edgesCoordinates.begin(), edgesCoordinates.end());
    random_shuffle(restCoordentate.begin(), restCoordentate.end());
    random_shuffle(bestEdgesCoordinates.begin(), bestEdgesCoordinates.end());

    for(auto coordinate : restCoordentate) {
        Vec3b color = image.at<Vec3b>(coordinate[0], coordinate[1]);
        
        circle(points, Point(coordinate[1], coordinate[0]), 3, color, -1, LINE_AA);
    }
    for(auto coordinate : edgesCoordinates) {
        Vec3b color = image.at<Vec3b>(coordinate[0], coordinate[1]);
        
        circle(points, Point(coordinate[1], coordinate[0]), 2, color, -1, LINE_AA);
    }
    for(auto coordinate : bestEdgesCoordinates) {
        Vec3b color = image.at<Vec3b>(coordinate[0], coordinate[1]);
        
        circle(points, Point(coordinate[1], coordinate[0]), 1, color, -1, LINE_AA);
    }
    
}

void on_trackbar_canny(int, void*){
    getPointillisticImage();
    imshow("Canny Points", points);
}

int main(int argc, char**argv) {
    if(argc < 2) {
        cout << "Imagem como segundo argumento necessaria!\n";
        return -1;
    }
    
    image = imread(argv[1], IMREAD_COLOR);
    if(!image.data) {
        cout << "Error ao carregar a imagem!\n";
        return -1;
    }

    sprintf(TrackbarName, "Threshold");
    namedWindow("Canny Points", WINDOW_KEEPRATIO);

    createTrackbar(
        TrackbarName, 
        "Canny Points",
        &canny_slider,
        canny_slider_max,
        on_trackbar_canny
    );
    on_trackbar_canny(canny_slider, 0);

    waitKey(0);
    imwrite("canny.png", points);
    return 0;
}