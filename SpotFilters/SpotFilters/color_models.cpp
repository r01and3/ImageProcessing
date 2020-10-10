#include "color_models.h"

Mat color_models::_BGR2YCrCb(Mat& _img) {
	Mat YCC = Mat::zeros(_img.rows, _img.cols, _img.type());
	float delta;
	if (_img.depth() == CV_8U)
		delta = _8_BIT;
	else if (_img.depth() == CV_16U)
		delta = _16_BIT;
	else
		delta = _F_P;
	for (int x = 0; x < _img.rows; x++)
		for (int y = 0; y < _img.cols; y++) {
			Vec3b color = _img.at<Vec3b>(x, y);
			Vec3b YCCcolor = YCC.at<Vec3b>(x, y);
			YCCcolor[0] = saturate_cast<uchar>(0.299 * color[2] + 0.587 * color[1] + 0.144 * color[2]);
			YCCcolor[1] = saturate_cast<uchar>((color[2] - YCCcolor[0]) * 0.713 + delta);
			YCCcolor[2] = saturate_cast<uchar>((color[0] - YCCcolor[0]) * 0.564 + delta);
			YCC.at<Vec3b>(x, y) = YCCcolor;
		}
	return YCC;
}

Mat color_models::_YCrCb2BGR(Mat& _img) {
	Mat BGR = Mat::zeros(_img.rows, _img.cols, _img.type());
	float delta;
	if (_img.depth() == CV_8U)
		delta = _8_BIT;
	else if (_img.depth() == CV_16U)
		delta = _16_BIT;
	else
		delta = _F_P;
	for (int x = 0; x < _img.rows; x++)
		for (int y = 0; y < _img.cols; y++) {
			Vec3b color = _img.at<Vec3b>(x, y);
			Vec3b BGRcolor = BGR.at<Vec3b>(x, y);
			BGRcolor[2] = saturate_cast<uchar>(color[0] + 1.403 * (color[1] - delta));
			BGRcolor[1] = saturate_cast<uchar>(color[0] - 0.714 * (color[1] - delta) - 0.344 * (color[2] - delta));
			BGRcolor[0] = saturate_cast<uchar>(color[0] + 1.773 * (color[2] - delta));
			BGR.at<Vec3b>(x, y) = BGRcolor;
		}
	return BGR;
}

Mat color_models::_BGR_Increase_Brightness(Mat& _img) {
	Mat result = Mat::zeros(_img.rows, _img.cols, _img.type());
	for (int x = 0; x < _img.rows; x++)
		for (int y = 0; y < _img.cols; y++) {
			Vec3b color = _img.at<Vec3b>(x, y);
			Vec3b result_color = result.at<Vec3b>(x, y);
			for (int z = 0; z < _img.channels(); z++)
				color[z] = saturate_cast<uchar>(color[z] + BRIGHTNESS);
			result.at<Vec3b>(x, y) = color;
		}
	return result;
}

Mat color_models::_YCrCb_Increase_Brightness(Mat& _img) {
	Mat result = Mat::zeros(_img.rows, _img.cols, _img.type());
	for (int x = 0; x < _img.rows; x++)
		for (int y = 0; y < _img.cols; y++) {
			Vec3b color = _img.at<Vec3b>(x, y);
			color[0] = saturate_cast<uchar>(color[0] + BRIGHTNESS);
			result.at<Vec3b>(x, y) = color;
		}
	return result;
}