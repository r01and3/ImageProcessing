#include "color_models.h"
#include<iostream>
#include "metric.h"

int main() {
	Mat img, res, ex, c;
	img = imread("green1.png", IMREAD_COLOR); // imread - ������ ��������
	res = color_models::_BGR2YCrCb(img);
	cvtColor(img, img, COLOR_BGR2YCrCb); // cvtColor - ������� � ������ ������
	resize(res, c, img.size()); 
	float metric = ssim(img, c);
	std::cout << "SSIM = " << metric;
	res = color_models::_YCrCb_Increase_Brightness(res);
	img.convertTo(ex, -1, 1, 30); // convertTo - ����������� �����
	imshow("example", ex); // imshow - ����� ���� � ������������
	imshow("img", img);
	imshow("result", res);
	imwrite("res.png", res);
	waitKey(0);
}