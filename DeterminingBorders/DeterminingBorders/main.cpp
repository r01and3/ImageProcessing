#include "DeterminingBorders.h"

int main() {
	Mat img = imread("tati.jpg", IMREAD_COLOR);
	cout << "Please wait while Canny's algorithm is executed\n";
	Mat res1 = DeterminingBorders::CannyAlgorithm(img);
	imshow("Canny", res1);
	waitKey(0);
	cout << "Please wait until the distance map is counted\n";
	Mat res2 = DeterminingBorders::distanceTransform(img);
	imshow("DistanceTransform", res2);
	waitKey(0);
	cout << "Wait until the 'watershed' algorithm is executed\n";
	Mat res3 = DeterminingBorders::watershed(img);
	imshow("Watershed", res3);
	waitKey(0);
}