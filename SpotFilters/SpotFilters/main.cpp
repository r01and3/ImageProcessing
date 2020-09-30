#include "color_models.h"

int main() {
	Mat img, res, ex;
	img = imread("green.png", IMREAD_COLOR); // imread - ������ ��������
	res = color_models::_BGR2YCrCb(img);
	cvtColor(img, img, COLOR_BGR2YCrCb); // cvtColor - ������� � ������ ������
	res = color_models::_YCrCb_Increase_Brightness(res);
	img.convertTo(ex, -1, 1, 30); // convertTo - ����������� �����
	imshow("example", ex); // imshow - ����� ���� � ������������
	imshow("img", img);
	imshow("result", res);
	waitKey(0);
}