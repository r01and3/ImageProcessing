#include "color_models.h"

int main() {
	Mat img, res, ex;
	img = imread("green.png", IMREAD_COLOR); // imread - читает картинку
	res = color_models::_BGR2YCrCb(img);
	cvtColor(img, img, COLOR_BGR2YCrCb); // cvtColor - перевод в другой формат
	res = color_models::_YCrCb_Increase_Brightness(res);
	img.convertTo(ex, -1, 1, 30); // convertTo - конвертация цвета
	imshow("example", ex); // imshow - вывод окна с изображением
	imshow("img", img);
	imshow("result", res);
	waitKey(0);
}