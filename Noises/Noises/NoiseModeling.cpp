#include "NoiseModeling.h"

Mat NoiseModeling::rayleNoise(const Mat& _img, float a, float b) {
	Mat res = Mat::zeros(_img.rows, _img.cols, _img.type());
	for (int i = 0; i < _img.rows; i++)
		for (int j = 0; j < _img.cols; j++) 
			for (int c = 0; c < _img.channels(); c++) {
				Vec3b color = _img.at<Vec3b>(i, j);
				double r = (double)rand() / RAND_MAX;
				res.at<Vec3b>(i, j)[c] = saturate_cast<uchar>(color[c] + 255 * (a + sqrt(-b * log(1 - r))));
			}
	return res;
}