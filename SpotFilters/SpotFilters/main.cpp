#include "color_models.h"
#include<iostream>
#include "metric.h"

int main() {
	Mat img, res, ex, c;
	img = imread("green1.png", IMREAD_COLOR); // imread - читает картинку
	res = color_models::_BGR2YCrCb(img);
	cvtColor(img, img, COLOR_BGR2YCrCb); // cvtColor - перевод в другой формат
	resize(res, c, img.size()); 
	float metric = ssim(img, c);
	std::cout << "SSIM = " << metric;
	res = color_models::_YCrCb_Increase_Brightness(res);
	img.convertTo(ex, -1, 1, 30); // convertTo - конвертация цвета
	imshow("example", ex); // imshow - вывод окна с изображением
	imshow("img", img);
	imshow("result", res);
	imwrite("res.png", res);
	waitKey(0);
}