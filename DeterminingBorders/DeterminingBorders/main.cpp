#include "DeterminingBorders.h"

int main() {
	Mat img = imread("steam.jpg", IMREAD_COLOR);
	Mat res = DeterminingBorders::distanceTransform(img);
	//Mat tmp = DeterminingBorders::CannyAlgorithm(img);
	imshow("dif1.png", res);
	//imshow("dif2.png", tmp);
	waitKey(0);
}