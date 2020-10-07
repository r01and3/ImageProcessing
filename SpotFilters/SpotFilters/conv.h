#pragma once
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
class con{
public:
	static Mat _mono(Mat& _img);
	static Mat _def(Mat& _img);
};