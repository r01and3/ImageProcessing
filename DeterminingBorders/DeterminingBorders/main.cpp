#include "DeterminingBorders.h"

int main() {
	Mat img = imread("steam.jpg", IMREAD_COLOR);
	Mat test, res;
	cvtColor(img, test, COLOR_BGR2GRAY);
	res = DeterminingBorders::gaussianFilter(test, 7, 1.0);
	vector<int> deg(img.rows * img.cols);
	vector<int>::iterator it = deg.begin();
	test = DeterminingBorders::sobelOperator(res, it);
	res = DeterminingBorders::nonMaxSuppression(test, deg);
	test = DeterminingBorders::thresholding(res, 120, 70);
	res = DeterminingBorders::tracing(test);
	imwrite("tati1.png", test);
	imwrite("tati2.png", res);
	waitKey(0);
}