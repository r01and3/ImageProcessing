#include <opencv2/opencv.hpp>
#include <iostream>
#include "NoiseModeling.h"
#include "DenoisingFilters.h"
#include "utils.h"
#include <time.h>

using namespace cv;

void noiseGenerationTest(const Mat& _img) {
	std::cout << "Noise generation script(Rayle Noise)\n";
	clock_t start = clock();
	Mat res = NoiseModeling::rayleNoise(_img, 0.2f, 0.005f);
	clock_t end = clock();
	imshow("result", res);
	waitKey(0);
	std::cout << "Execution time: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
}

void denoisingAvgGeomTest(const Mat& _img) {
	std::cout << "Denoising script\n";
	Mat noise = NoiseModeling::rayleNoise(_img, 0.2f, 0.005f);
	std::cout << "Filter noise reduction script geometric mean\n";
	clock_t start = clock();
	Mat denoise = DenoisingFilters::avgGeomFilter(noise, 3);
	clock_t end = clock();
	imshow("noise image", noise);
	imshow("denoise image", denoise); 
	waitKey(0);
	std::cout << "Execution time: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
}

void denoisingMedianAndComparisonOPENCVTest(const Mat& _img) {
	std::cout << "Denoising script\n";
	Mat noise = NoiseModeling::rayleNoise(_img, 0.1f, 0.005f);
	std::cout << "Filter noise reduction script median\n";
	clock_t start = clock();
	Mat mydenoise = DenoisingFilters::medianFilter(noise, 3);
	clock_t end = clock();
	std::cout << "Execution time: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
	Mat opencvdenoise;
	start = clock();
	medianBlur(noise, opencvdenoise, 3);
	end = clock();
	std::cout << "Execution time: " << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
	std::cout << "Comparison of the quality of work of our own implementation with the opencv implementation according to the PSNR metric\n";
	std::cout << ::utils::PSNR(mydenoise, opencvdenoise) << "dB\n";
	imshow("my denoise", mydenoise);
	imshow("opencv denoise", opencvdenoise);
	waitKey(0);
}
 
int main() {
	int f = 1;
	std::cout << "Test application start\n";
	Mat img = imread("syn.jpg", IMREAD_COLOR);
	std::cout << "Original image\n";
	imshow("image", img);
	waitKey(0);
	while (f) {
		std::cout << "Enter 1 if you want to run the noise generation script.\n";
		std::cout << "Enter 2 if you want to run noise removal script using geometric mean.\n";
		std::cout << "Enter 3 if you want to run a noise removal script with a median filter and compare with opencv implementation.\n";
		std::cout << "Enter any other number if you want to terminate the program.\n";
		std::cin >> f;
		switch (f)
		{
		case 1:
			noiseGenerationTest(img);
			break;
		case 2:
			denoisingAvgGeomTest(img);
			break;
		case 3:
			denoisingMedianAndComparisonOPENCVTest(img);
			break;
		default:
			f = 0;
			break;
		}
	}
}