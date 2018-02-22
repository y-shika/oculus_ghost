// vision_augmentation.cpp
// simple image processing for vision augmentation

// OpenCV
#include <opencv2/opencv.hpp>
//using namespace cv;

bool _va_init = false;
unsigned int _va_width, _va_height, _va_pixelsize;
cv::Mat cv_src, cv_grey, cv_dst;
int va_canny_arg1 = 50;
int va_canny_arg2 = 200;

bool va_init(unsigned int width, unsigned int height, unsigned int pixelsize) {

	if (_va_init) return false;

	if (pixelsize != 4) return false;
	_va_width = width, _va_height = height, _va_pixelsize = pixelsize;

	cv_src = cv::Mat(_va_height, _va_width, CV_8UC4);
	cv_grey = cv::Mat(_va_height, _va_width, CV_8UC1);
	cv_dst = cv::Mat(_va_height, _va_width, CV_8UC4);
	_va_init = true;
	return true;
}

unsigned char* va_effect(unsigned char* src, unsigned int width, unsigned int height, unsigned int pixelsize) {
	cv::Mat cv_rgb;
	if (!_va_init) return NULL;
	if (_va_width != width || _va_height != height || _va_pixelsize != pixelsize) return NULL;

	memcpy(cv_src.data, src, _va_width * _va_height * _va_pixelsize);
	cv::cvtColor(cv_src, cv_rgb, cv::COLOR_BGRA2BGR);
	cv::cvtColor(cv_rgb, cv_dst, cv::COLOR_BGR2BGRA);
	return cv_dst.data;
}

bool va_close() {
	if (!_va_init) return false;

	_va_init = false;
	return true;
}
