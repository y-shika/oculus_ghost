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

/*
void start(float x, float y, float z)
{
	std::stringstream ss;
	ss << x << ", " << y << ", " << z;

	//cv::putText(cv_src, ss.str() , cv::Point2f(50, .0f),
	//	cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 4, CV_AA);
	cv::putText(cv_src, "Test" , cv::Point2f(50, .0f),
		cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 4, CV_AA);
}
*/

unsigned char* va_effect(unsigned char* src, unsigned int width, unsigned int height, unsigned int pixelsize, float x, float y, float z) {
	cv::Mat cv_rgb;
	if (!_va_init) return NULL;
	if (_va_width != width || _va_height != height || _va_pixelsize != pixelsize) return NULL;

	//std::stringstream ss;
	//ss << x << ", " << y << ", " << z;

	memcpy(cv_src.data, src, _va_width * _va_height * _va_pixelsize);
	cv::cvtColor(cv_src, cv_rgb, cv::COLOR_BGRA2BGR);
	//cv::imshow("rgb", cv_rgb);
	//cv::waitKey(1);

	//cv::putText(cv_rgb, ss.str(), cv::Point2f(50, 500),
	//cv::FONT_HERSHEY_SIMPLEX, 1.5, cv::Scalar(0, 255, 0), 4, CV_AA);
	cv::cvtColor(cv_rgb, cv_dst, cv::COLOR_BGR2BGRA);
	return cv_dst.data;
}

/*
unsigned char* va_effect(unsigned char* src, unsigned int width, unsigned int height, unsigned int pixelsize) {
	if (!_va_init) return NULL;
	if (_va_width != width || _va_height != height || _va_pixelsize != pixelsize) return NULL;

	memcpy(cv_src.data, src, _va_width * _va_height * _va_pixelsize);
	//cv::Canny(cv_src, cv_grey, va_canny_arg1, va_canny_arg2);
	//cv::cvtColor(cv_grey, cv_dst, CV_GRAY2BGRA);
	cv::cvtColor(cv_src, cv_dst, CV_RGB2BGR);
	return cv_dst.data;
}
*/

bool va_close() {
	if (!_va_init) return false;

	_va_init = false;
	return true;
}
