#pragma once
#define _USE_MATH_DEFINES
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace cv;

class NoiseModeling {
public:
	static Mat rayleNoise(const Mat& _img, float a, float b);
};