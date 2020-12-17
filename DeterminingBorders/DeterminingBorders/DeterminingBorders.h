#pragma once
#include <opencv2/opencv.hpp>
#include <math.h>
#include <numeric>

#define M_PI 3.14159265358979323846

using namespace cv;
using namespace std;

template<class T>
T clamp(T src, T min, T max) {
	if (src < min) {
		return min;
	} else if (src > max) {
		return max;
	} else {
		return src;
	}
}

template<class T>
int sign(T src) {
	if (src > 0) return 1;
	else if (src < 0) return -1;
	else return 0;
}

namespace DeterminingBorders {
	double gaussianFunc(int x, int y, double sigma);
	vector<double> gaussianKernel(int size, double sigma);
	Mat gaussianFilter(const Mat& _img, int size, double sigma);
	
	const int xSobelKernel[] = {
		1, 0, -1,
		2, 0, -2,
		1, 0, -1
	};

	const int ySobelKernel[] = {
		1, 2, 1,
		0, 0, 0,
		-1, -2, -1
	};

	Mat sobelOperator(const Mat& _img, vector<int>::iterator it);
	Mat nonMaxSuppression(const Mat& _img, vector<int>& deg);
	Mat thresholding(const Mat& _img, uchar high_pr, uchar low_pr);
	Mat tracing(const Mat& _img);

	Mat CannyAlgorithm(const Mat& _img);
}
