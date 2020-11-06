#pragma once
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <math.h>
#include <algorithm>


using namespace cv;

class DenoisingFilters {
private:
	static float avgGeomColor(const Mat& _img, int channel, int x, int y, int radius);
	static float medianColor(const Mat& _img, int channel, int x, int y, int radius);
public:
	static Mat avgGeomFilter(const Mat& _img, int _n);
	static Mat medianFilter(const Mat& _img, int _n);
};