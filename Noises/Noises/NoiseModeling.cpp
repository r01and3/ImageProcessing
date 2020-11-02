#include "NoiseModeling.h"

int NoiseModeling::riley(int a, int b, int z) {
	if (z < a) return 0;
	else {
		return saturate_cast<uchar>(((2.0f / b) * (z - a) * exp(- (float)((z - a) * (z - a)) / b)) * 255);
	}
}

Mat NoiseModeling::constatntNoise(const Mat& _img) {
	Mat result = Mat::zeros(_img.rows, _img.cols, _img.type());
	for (int i = 0; i < _img.rows; i++)
		for (int j = 0; j < _img.cols; j++) {
			uchar color = _img.at<uchar>(i, j);
			result.at<uchar>(i, j) = color < 100 && color > 0 ? saturate_cast<uchar>(color + (1.0f / 100.0f) * 255) : saturate_cast<uchar>(color);
		}
	return result;
}

Mat NoiseModeling::rileyNoise(const Mat& _img, int a, int b) {
	Mat result = Mat::zeros(_img.rows, _img.cols, _img.type());
	for (int i = 0; i < _img.rows; i++)
		for (int j = 0; j < _img.cols; j++) 
			for (int c = 0; c < _img.channels(); c++) {
				uchar color = _img.at<Vec3b>(i, j)[c];
				result.at<Vec3b>(i, j)[c] = saturate_cast<uchar>(color + riley(a, b, color));
			}
	return result;
}