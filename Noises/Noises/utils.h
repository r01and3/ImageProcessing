#pragma once
#include <opencv2/opencv.hpp>

namespace utils {
	float itensity(cv::Vec3b color);
	float MSE(const cv::Mat& _img1, const cv::Mat& _img2);
	float PSNR(const cv::Mat& _img1, const cv::Mat& _img2);
}