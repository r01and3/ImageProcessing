#pragma once
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#define _8_BIT 128
#define _16_BIT 32768
#define _F_P 0.5
#define BRIGHTNESS 30

using namespace cv;

class color_models {
public:
	static Mat _BGR2YCrCb(Mat& _img);
	static Mat _YCrCb2BGR(Mat& _img);
	static Mat _BGR_Increase_Brightness(Mat& _img);
	static Mat _YCrCb_Increase_Brightness(Mat& _img);
};