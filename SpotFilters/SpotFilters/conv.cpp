#include "conv.h"

Mat con::_mono(Mat& _img) {
	Mat im = Mat::zeros(_img.rows, _img.cols, _img.type());
	for (int x = 0; x < _img.rows; x++)
		for (int y = 0; y < _img.cols; y++) {
			Vec3b color = _img.at<Vec3b>(x, y);
			for (int c = 0; c < _img.channels(); c++)
			color[c] = ((_img.at<Vec3b>(x, y)[0] + _img.at<Vec3b>(x, y)[1] + _img.at<Vec3b>(x, y)[2]) / 3);
			im.at<Vec3b>(x, y) = color;
		}
	return im;
}
Mat con::_def(Mat& _img) {
	Mat grey;
	cvtColor(_img, grey, COLOR_BGR2GRAY);
	return grey;
}