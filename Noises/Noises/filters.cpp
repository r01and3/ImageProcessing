#include "filters.h"

/*template <class T>
T clamp(T v, int max, int min)
{
	if (v > max)
		return max;
	else if (v < min)
		return min;
	return v;
}*/

Mat filters::avg_geom(const Mat& img) {
	Mat res = Mat::zeros(img.rows, img.cols, img.type());
	Mat padimg;
	int mean = 0.0, final = 0.0;
	int cols = img.cols, rows = img.cols;
	int ksize = 5;
	int padsize = (ksize - 1) / 2;
	copyMakeBorder(img,padimg, padsize, padsize, padsize, padsize, BORDER_DEFAULT);
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			for (int x = -padsize; x <= padsize; x++) {
				for (int y = padsize; y <= padsize; y++) {
					mean += padimg.at<uchar>(i + x, j + y);
				}
			}
			mean = mean / (ksize * ksize);
			final = round(mean);
			res.at<Vec3b>(i - padsize, j - padsize) = saturate_cast<uchar>(final);
		}
	}
	return res;
}
	/*Mat temp(Size(99, 99), CV_8UC3);
	float t = temp.rows * temp.cols;
	for (int i = 0; img.rows < temp.rows; i++)
		for(int j = 0; img.cols < temp.cols; i++) {
			Vec3b color = img.at<Vec3b>(i, j);
			for (int c = 0; c < img.channels(); c++)
				color[c] = img.at<Vec3b>(i, j)[c];
			temp.at<Vec3b>(i, j) = color;
				temp.rows = img.rows;
				temp.cols = img.cols;
	}*/
/*	Mat res = Mat::zeros(img.rows, img.cols, img.type());
		for (int i = 0; i < img.rows; i++)
			for (int j = 0; j < img.cols; j++)
				for (int c = 0; c < img.channels(); c++) {

				}*/
/*
Mat filters::median(const Mat& img, int x, int y, int radius) {
	int mRadius = radius;
	int size = 2 * mRadius + 1;
	Mat res = Mat::zeros(img.rows, img.cols, img.type());
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++) {
			res.at<Vec3b>(i, j)[0] = (size * size);
			res.at<Vec3b>(i, j)[1] = (size * size);
			res.at<Vec3b>(i, j)[2] = (size * size);
		}
	for (int i = -mRadius; i <= mRadius; i++)
		for (int j = -mRadius; j <= mRadius; j++) {
				int idx = (i + mRadius) * size + j + mRadius;
				for (int c = 0; c < img.channels(); c++) {
				Vec3b color = img.at<Vec3b>(clamp<int>(x + j, img.size().width - 1, 0),
					clamp<int>(y + i, img.size().height - 1, 0));
				res.at<Vec3b>(i, j)[0] = color[0];
				res.at<Vec3b>(i, j)[1] = color[1];
				res.at<Vec3b>(i, j)[2] = color[3];
			}
		}
	return res;
}
*/