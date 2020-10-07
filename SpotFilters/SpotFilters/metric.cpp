#include "metric.h"
using namespace cv;
float ssim(const Mat& _img, const Mat& _emg)
{
	if ((_img.rows != _emg.rows) || (_img.cols != _emg.cols))
		throw("");
	Mat img, emg;
	cvtColor(_img, img,  COLOR_BGR2GRAY);
	cvtColor(_emg, emg, COLOR_BGR2GRAY);
	int n = img.rows * img.cols;
	float avgX = 0, avgY = 0;
	for (int y = 0; y < img.rows; y++)
		for (int x = 0; x < img.cols; x++) {
			avgX += img.at<uchar>(y, x);
			avgY += emg.at<uchar>(y, x);
		}
	avgX /= n;
	avgY /= n;
	float dX = 0, dY = 0, c = 0;
	for (int y = 0; y < img.rows; y++)
		for (int x = 0; x < img.cols; x++) {
			dX += (img.at<uchar>(y, x) - avgX) * (img.at<uchar>(y, x) - avgX);
			dY += (emg.at<uchar>(y, x) - avgY) * (emg.at<uchar>(y, x) - avgY);
			c += (img.at<uchar>(y, x) - avgX) * (emg.at<uchar>(y, x) - avgY);
		}
	dX /= (n - 1);
	dY /= (n - 1);
	c /= (n - 1);
	float c1 = 0.01 * 255 * 0.01 * 255;
	float c2 = 0.03 * 255 * 0.03 * 255;
	float ssim = ((2 * avgX * avgY + c1) * (2 * c + c2)) /
		((avgX * avgX + avgY * avgY + c1) * (dX + dY + c2));
	return ssim;
}