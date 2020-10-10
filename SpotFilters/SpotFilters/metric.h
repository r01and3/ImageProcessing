#pragma once
#include <opencv2/opencv.hpp>

using namespace cv;

class metric {
public:
	static float ssim(const Mat& _img, const Mat& _emg);
};
