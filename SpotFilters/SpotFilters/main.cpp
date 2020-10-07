#include "color_models.h"
#include<iostream>
#include "metric.h"
#include "conv.h"

int main() {
	Mat img, res, ex, c, m, gr;
	img = imread("green1.png", IMREAD_COLOR); // imread - ������ ��������
	res = color_models::_BGR2YCrCb(img);
	cvtColor(img, img, COLOR_BGR2YCrCb); // cvtColor - ������� � ������ ������
	m = con::_mono(img);
	gr = con::_def(img);
	resize(res, c, img.size()); 
	float metric = ssim(img, c);
	std::cout << "SSIM = " << metric;
	res = color_models::_YCrCb_Increase_Brightness(res);
	img.convertTo(ex, -1, 1, 30); // convertTo - ����������� �����
	imshow("example", ex); // imshow - ����� ���� � ������������
	imshow("img", img);
	imshow("result", res);
	imwrite("res.png", res);
	imshow("mono", m);
	imshow("bgr2gray", gr);
	waitKey(0);
}