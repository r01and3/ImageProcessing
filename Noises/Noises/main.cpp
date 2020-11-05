#include <opencv2/opencv.hpp>
#include <iostream>
#include "NoiseModeling.h"
#include "filters.h"

using namespace cv;

int main() {
	Mat img = imread("syn.jpg", IMREAD_ANYCOLOR), res, t, med, clean(700, 900, CV_8UC3, Scalar(0, 0, 0));
	//cvtColor(img, img, COLOR_BGR2GRAY);
	res = NoiseModeling::rayleNoise(img, 0.2f, 0.025f);
	//bilateralFilter(res, clean, 3, 200, 300);
	imshow("img", img);
	imshow("res", res);
	//imshow("clean", clean);
	t = filters::avg_geom(res);
	//imshow("med", med);
	imshow("t", t);
	waitKey(0);
}