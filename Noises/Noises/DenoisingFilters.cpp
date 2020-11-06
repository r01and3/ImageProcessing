#include "DenoisingFilters.h"

template <class T>
T clamp(T v, int max, int min)
{
	if (v > max)
		return max;
	else if (v < min)
		return min;
	return v;
}

float DenoisingFilters::avgGeomColor(const Mat& _img, int channel, int x, int y, int radius) {
	int n = radius * 2 + 1;
	float s = 0;
	for (int i = -radius; i < radius; i++)
		for (int j = -radius; j < radius; j++) {
			s += log(_img.at<Vec3b>(clamp<int>(y + j, _img.rows - 1, 0), clamp<int>(x + i, _img.cols - 1, 0))[channel] / 255.0f);
		}
	s /= n * n;
	return exp(s) * 255;
}

Mat DenoisingFilters::avgGeomFilter(const Mat& _img, int _n) {
	Mat res = Mat::zeros(_img.rows, _img.cols, _img.type());
	int radius = (_n - 1) / 2;
	for (int y = 0; y < _img.rows; y++)
		for (int x = 0; x < _img.cols; x++) {
			for (int c = 0; c < _img.channels(); c++) {
				res.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(avgGeomColor(_img, c, x, y, radius));
			}
		}
	return res;
}

float DenoisingFilters::medianColor(const Mat& _img, int channel, int x, int y, int radius) {
	int n = radius * 2 + 1;
	int* channel_value = new int[n * n];
	for (int i = -radius; i < radius; i++)
		for (int j = -radius; j < radius; j++) {
			int idx = (i + radius) * n + j + radius;
			uchar color = _img.at<Vec3b>(clamp<int>(y + j, _img.rows - 1, 0), clamp<int>(x + i, _img.cols - 1, 0))[channel];
			channel_value[idx] = color;
		}
	std::sort(channel_value, channel_value + n * n - 1);
	return channel_value[n * n / 2];
}

Mat DenoisingFilters::medianFilter(const Mat& _img, int _n) {
	Mat res = Mat::zeros(_img.rows, _img.cols, _img.type());
	int radius = (_n - 1) / 2;
	for (int y = 0; y < _img.rows; y++)
		for (int x = 0; x < _img.cols; x++) {
			for (int c = 0; c < _img.channels(); c++) {
				res.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(medianColor(_img, c, x, y, radius));
			}
		}
	return res;
}