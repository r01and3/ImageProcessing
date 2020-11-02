#include <opencv2/opencv.hpp>
#include <iostream>
#include "NoiseModeling.h"

using namespace cv;

int main() {
	Mat img = imread("syn.jpg", IMREAD_COLOR), res;
	//cvtColor(img, img, COLOR_BGR2GRAY);
	res = NoiseModeling::rileyNoise(img, 0, 10);
	imshow("img", img);
	imshow("res", res);
	waitKey(0);
}