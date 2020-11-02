#pragma once
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;

class NoiseModeling {
private:
	static int riley(int a, int b, int z);
public:
	static Mat constatntNoise(const Mat& _img);
	static Mat rileyNoise(const Mat& _img, int a, int b);
};