#include "utils.h"

float utils::itensity(cv::Vec3b color) {
	return color[0] * 0.11f + color[1] * 0.59f + color[2] * 0.3f;
}

float utils::MSE(const cv::Mat& _img1, const cv::Mat& _img2) {
	float mse = 0;
	cv::Mat img2;
	cv::resize(_img2, img2, cv::Size(_img1.cols, _img1.rows));
	for (int y = 0; y < _img1.rows; y++)
		for (int x = 0; x < _img1.cols; x++) {
			mse += abs(itensity(_img1.at<cv::Vec3b>(y, x)) - itensity(img2.at<cv::Vec3b>(y, x)));
		}
	return  mse / (_img1.cols * _img1.rows);
}

float utils::PSNR(const cv::Mat& _img1, const cv::Mat& _img2) {
	float mse = MSE(_img1, _img2);
	return 10.0f * log10((255.0f * 255.0f) / mse);
}