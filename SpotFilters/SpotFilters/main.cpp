#include "color_models.h"
#include "metric.h"
#include "conv.h"
#include <iostream>
#include <ctime>

using namespace std;

void color_models_test();
void gray_scale_test();
void increase_brightness_bgr_test();
void increase_brightness_ycrcb_test();

int main() {
	bool f = true;
	while (f) {
		cout << "Please select a test case" << endl;
		cout << "Enter 1 if you want to run 'grayscale' script" << endl;
		cout << "Enter 2 if you want to run the 'color model' script" << endl;
		cout << "Enter 3 if you want to run a script to increase the brightness of BGR images" << endl;
		cout << "Enter 4 if you want to run a script to increase the brightness of YCrCb images" << endl;
		cout << "Enter any other number if you want to exit" << endl;
		int s;
		cin >> s;
		switch (s)
		{
		case 1:
			gray_scale_test();
			break;
		case 2:
			color_models_test();
			break;
		case 3:
			increase_brightness_bgr_test();
			break;
		case 4:
			increase_brightness_ycrcb_test();
			break;
		default:
			f = false;
		}
	}
}

void color_models_test() {
	Mat myYCrCb, myBGR, cvYCrCb, cvBGR, img;
	img = imread("green.png", IMREAD_COLOR);
	clock_t start = clock();
	myYCrCb = color_models::_BGR2YCrCb(img);
	clock_t end = clock();
	cout << "My implementation BGR2YCrCb: time " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	start = clock();
	cvtColor(img, cvYCrCb, COLOR_BGR2YCrCb);
	end = clock();
	cout << "OPENCV implementation BGR2YCrCb: time " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	cout << "Comparison of OPENCV implementation with your own implementation using the developed metric " << metric::ssim(cvYCrCb, myYCrCb) << endl;
	start = clock();
	myBGR = color_models::_YCrCb2BGR(myYCrCb);
	end = clock();
	cout << "My implementation YCrCb2BGR: time " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	start = clock();
	cvtColor(img, cvBGR, COLOR_YCrCb2BGR);
	end = clock();
	cout << "OPENCV implementation YCrCb2BGR: time " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	cout << "Comparison of OPENCV implementation with your own implementation using the developed metric " << metric::ssim(cvBGR, myBGR) << endl;
	imshow("myYCrCb", myYCrCb);
	imshow("cvYCrCb", cvYCrCb);
	imshow("myBGR", myBGR);
	imshow("cvBGR", cvBGR);
	waitKey(0);
}

void gray_scale_test() {
	Mat myGrayScale, cvGrayScale, img;
	img = imread("green.png", IMREAD_COLOR);
	clock_t start = clock();
	myGrayScale = con::_mono(img);
	clock_t end = clock();
	cout << "My implementation GrayScale: time " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	start = clock();
	cvGrayScale = con::_def(img);
	end = clock();
	cout << "OPENCV implementation GrayScale: time " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	imshow("myGrayScale", myGrayScale);
	imshow("cvGrayScale", cvGrayScale);
	waitKey(0);
}

void increase_brightness_bgr_test() {
	Mat myib, cvib, img;
	img = imread("green.png", IMREAD_COLOR);
	clock_t start = clock();
	myib = color_models::_BGR_Increase_Brightness(img);
	clock_t end = clock();
	cout << "My implementation GrayScale: time " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	start = clock();
	img.convertTo(cvib, -1, 1, 30);
	end = clock();
	cout << "OPENCV implementation GrayScale: time " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	cout << "Comparison of OPENCV implementation with your own implementation using the developed metric " << metric::ssim(cvib, myib) << endl;
	imshow("myib", myib);
	imshow("cvib", cvib);
	waitKey(0);
}

void increase_brightness_ycrcb_test() {
	Mat myib, cvib, img;
	img = imread("green.png", IMREAD_COLOR);
	myib = color_models::_BGR2YCrCb(img);
	clock_t start = clock();
	myib = color_models::_YCrCb_Increase_Brightness(myib);
	clock_t end = clock();
	cout << "My implementation GrayScale: time " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	cvtColor(img, cvib, COLOR_BGR2YCrCb);
	start = clock();
	cvib.convertTo(cvib, -1, 1, 30);
	end = clock();
	cout << "OPENCV implementation GrayScale: time " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	cout << "Comparison of OPENCV implementation with your own implementation using the developed metric " << metric::ssim(cvib, myib) << endl;
	imshow("myib", myib);
	imshow("cvib", cvib);
	waitKey(0);
}