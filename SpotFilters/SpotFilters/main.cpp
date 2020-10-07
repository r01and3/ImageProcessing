#include "color_models.h"
#include<iostream>
#include "metric.h"
#include "conv.h"

int main() {
	Mat img, res, ex, c, m, gr;
	img = imread("green1.png", IMREAD_COLOR); // imread - читает картинку
	res = color_models::_BGR2YCrCb(img);
	cvtColor(img, img, COLOR_BGR2YCrCb); // cvtColor - перевод в другой формат
	m = con::_mono(img);
	gr = con::_def(img);
	resize(res, c, img.size()); 
	float metric = ssim(img, c);
	std::cout << "SSIM = " << metric;
	res = color_models::_YCrCb_Increase_Brightness(res);
	img.convertTo(ex, -1, 1, 30); // convertTo - конвертация цвета
	imshow("example", ex); // imshow - вывод окна с изображением
	imshow("img", img);
	imshow("result", res);
	imwrite("res.png", res);
	imshow("mono", m);
	imshow("bgr2gray", gr);
	waitKey(0);
}