#include "DeterminingBorders.h"

int angleQuantization(double deg) {
	if (deg <= 22) return 0;
	else if (deg <= 67) return 45;
	else if (deg <= 112) return 90;
	else if (deg <= 135) return 135;
	else return 180;
}

bool check(const Mat& _img, int x, int y, uchar v) {
	if (x < 0 || x > _img.cols - 1 || y < 0 || y > _img.rows - 1) return false;
	else if (_img.at<uchar>(y, x) <= v) return true;
	else return false;
}

int EDT_f(int y, int i, int g_i) {
	return (y - i) * (y - i) + (g_i * g_i);
}

int EDT_sep(int i, int u, int g_i, int g_u) {
	return floor((u * u - i * i + g_u * g_u - g_i * g_i) / (2 * (u - i)));
}

double DeterminingBorders::gaussianFunc(int x, int y, double sigma) {
	return (1.0 / (2 * M_PI * sigma * sigma)) * exp(-(x * x + y * y) / (2 * sigma * sigma));
}

vector<double> DeterminingBorders::gaussianKernel(int size, double sigma) {
	vector<double> kernel(size * size);
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			kernel[y * size + x] = gaussianFunc(x, y, sigma);
		}
	}
	return kernel;
}

Mat DeterminingBorders::gaussianFilter(const Mat& _img, int size, double sigma) {
	Mat filteredImage = Mat::zeros(_img.rows, _img.cols, _img.type());
	int radius = size / 2;
	vector<double> kernel = gaussianKernel(size, sigma);
	double norm = accumulate(kernel.begin(), kernel.end(), 0.0);

	for (int y = 0; y < _img.rows; y++) {
		for (int x = 0; x < _img.cols; x++) {
			double color = 0.0;
			for (int j = -radius; j <= radius; j++) {
				for (int i = -radius; i <= radius; i++) {
					int idxX = clamp<int>(x + i, 0, _img.cols - 1), idxY = clamp<int>(y + j, 0, _img.rows - 1);
					//int idxX = x + i, idxY = y + j;
					color += _img.at<uchar>(idxY, idxX) * kernel[(j + radius) * size + (i + radius)];
				}
			}
			filteredImage.at<uchar>(y, x) = saturate_cast<uchar>(color / norm);
		}
	}

	return filteredImage;
}

Mat DeterminingBorders::sobelOperator(const Mat& _img, vector<int>::iterator it) {
	Mat filteredImage = Mat::zeros(_img.rows, _img.cols, _img.type());

	for (int y = 1; y < _img.rows - 2; y++) {
		for (int x = 1; x < _img.cols - 2; x++) {
			double gradientX = 0.0, gradientY = 0.0;
			for (int j = -1; j <= 1; j++) {
				for (int i = -1; i <= 1; i++) {
					int idxX = x + i, idxY = y + j;
					gradientX += _img.at<uchar>(idxY, idxX) * xSobelKernel[(j + 1) * 3 + (i + 1)];
					gradientY += _img.at<uchar>(idxY, idxX) * ySobelKernel[(j + 1) * 3 + (i + 1)];
				}
			}
			filteredImage.at<uchar>(y, x) = saturate_cast<uchar>(sqrt(gradientX * gradientX + gradientY * gradientY));
			//double teta = gradientX == 0 && gradientY == 0 ? 180 : (round(atan2(gradientX, gradientY) * 4 / M_PI) * M_PI / 4 - M_PI / 2) * 180;
			double teta = gradientX == 0 ? 180 : atan(gradientY / gradientX) * 180;
			*it = angleQuantization(teta);
		}
	}

	return filteredImage;
}

Mat DeterminingBorders::nonMaxSuppression(const Mat& _img, vector<int>& deg) {
	Mat filteredImage = Mat::zeros(_img.rows, _img.cols, _img.type());

	for (int y = 0; y < _img.rows; y++) {
		for (int x = 0; x < _img.cols; x++) {
			if (deg[y * _img.cols + x] == 180) continue;
			int dx = sign<double>(cos(deg[y * _img.cols + x] * M_PI / 180));
			int dy = -sign<double>(sin(deg[y * _img.cols + x] * M_PI / 180));
			if (check(_img, x + dx, y + dy, _img.at<uchar>(y, x))) filteredImage.at<uchar>(y + dy, x + dx) = 0;
			if (check(_img, x - dx, y - dy, _img.at<uchar>(y, x))) filteredImage.at<uchar>(y - dy, x - dx) = 0;
			filteredImage.at<uchar>(y, x) = _img.at<uchar>(y, x);
		}
	}

	return filteredImage;
}

Mat DeterminingBorders::thresholding(const Mat& _img, uchar high_pr, uchar low_pr) {
	Mat filteredImage = Mat::zeros(_img.rows, _img.cols, _img.type());

	for (int y = 0; y < _img.rows; y++) {
		for (int x = 0; x < _img.cols; x++) {
			if (_img.at<uchar>(y, x) >= high_pr) filteredImage.at<uchar>(y, x) = 255;
			else if (_img.at<uchar>(y, x) < high_pr && _img.at<uchar>(y, x) >= low_pr) filteredImage.at<uchar>(y, x) = 127;
			else filteredImage.at<uchar>(y, x) = 0;
		}
	}

	return filteredImage;
}

Mat DeterminingBorders::tracing(const Mat& _img) {
	Mat filteredImage = Mat::zeros(_img.rows, _img.cols, _img.type());

	for (int y = 1; y < _img.rows - 2; y++) {
		for (int x = 1; x < _img.cols - 2; x++) {
			if (_img.at<uchar>(y, x) == 127) {
				for (int j = -1; j <= 1; j++) {
					bool f = false;
					for (int i = -1; i <= 1; i++) {
						int idxX = x + i, idxY = y + j;
						if (_img.at<uchar>(idxY, idxX) == 255) {
							filteredImage.at<uchar>(y, x) = 255;
							f = true;
							break;
						}
					}
					if (f) break;
				}
			}
		}
	}

	return filteredImage;
}

Mat DeterminingBorders::CannyAlgorithm(const Mat& _img) {
	Mat result = Mat::zeros(_img.rows, _img.cols, _img.type());
	cvtColor(_img, result, COLOR_BGR2GRAY);
	result = gaussianFilter(result, 7, 1.0);
	vector<int> deg(_img.rows * _img.cols);
	vector<int>::iterator it = deg.begin();
	result = sobelOperator(result, it);
	result = nonMaxSuppression(result, deg);
	result = thresholding(result, 80, 20);
	result = tracing(result);
	return result;
}

Mat DeterminingBorders::distanceTransform(const Mat& _img) {
	Mat result = Mat::zeros(_img.rows, _img.cols, _img.type());
	result = CannyAlgorithm(_img);
	
	for (int y = 1; y < _img.rows; y++) {
		for (int x = 1; x < _img.cols; x++) {
			if (result.at<uchar>(y, x) != 255) {
				int value = max((max(result.at<uchar>(y - 1, x), result.at<uchar>(y, x - 1)) - 1),
					result.at<uchar>(y - 1, x - 1) - 2);
				if (value < 0) value = 0;
				result.at<uchar>(y, x) = value;
			}
		}
	}

	for (int y = _img.rows - 2; y >= 0; y--) {
		for (int x = _img.cols - 2; x >= 0; x--) {
			if (result.at<uchar>(y, x) != 255) {
				int value = max((max(result.at<uchar>(y + 1, x), result.at<uchar>(y, x + 1)) - 1),
					result.at<uchar>(y + 1, x + 1) - 2);
				value = max(value, (int)result.at<uchar>(y, x));
				if (value < 0) value = 0;
				result.at<uchar>(y, x) = value;
			}
		}
	}

	/*for (int y = 0; y < _img.rows; y++) {
		if (result.at<uchar>(y, 0)) result.at<uchar>(y, 0) = 0;
		else result.at<uchar>(y, 0) = 255;
		for (int x = 1; x < _img.cols; x++) {
			if (result.at<uchar>(y, x)) result.at<uchar>(y, x) = 0;
			else result.at<uchar>(y, x) = 1 + result.at<uchar>(y, x - 1);
		}
		for (int x = _img.cols - 2; x >= 0; x--) {
			if (result.at<uchar>(y, x + 1) < result.at<uchar>(y, x)) 
				result.at<uchar>(y, x) = 1 + result.at<uchar>(y, x + 1);
		}
	}

	vector<int> s(_img.rows);
	vector<int> t(_img.rows);
	int q = 0;

	for (int x = 0; x < _img.cols; x++) {
		q = 0; s[0] = 0; t[0] = 0;
		for (int y = 1; y < _img.rows; y++) {
			while (q >= 0 && EDT_f(t[q], s[q], (int)result.at<uchar>(s[q], x)) >
				EDT_f(t[q], y, (int)result.at<uchar>(y, x))) q--;
			if (q < 0) {
				q = 0;
				s[0] = y;
			} else {
				int w = 1 + EDT_sep(s[q], y, (int)result.at<uchar>(s[q], x), (int)result.at<uchar>(y, x));
				if (w < _img.rows) {
					q++;
					s[q] = y;
					t[q] = w;
				}
			}
		}
		for (int y = _img.rows - 1; y >= 0; y--) {
			result.at<uchar>(y, x) = floor(sqrt(EDT_f(y, s[q], (int)result.at<uchar>(s[q], x))));
			if (y == t[q]) q--;
		}
	}*/

	return result;
}