#pragma once
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <math.h>


using namespace cv;

class filters {
public:
	static Mat avg_geom(const Mat& img);
	static Mat median(const Mat& img, int x, int y, int radius);
	static Mat avgGeomFilter(const Mat& _img, int _n);
};