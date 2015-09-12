#pragma once
#include <labutility.hpp>

void cvtColorBGR2PLANE(const cv::Mat& src, cv::Mat& dest);
void cvtColorPLANE2BGR(const cv::Mat& src, cv::Mat& dest);
class RedundantDXTDenoise
{
public:
	enum BASIS
	{
		DCT = 0,
		DHT = 1,
		DWT = 2//under construction
	};
	bool isSSE;
	
	void init(cv::Size size_, int color_, cv::Size patch_size_);
	RedundantDXTDenoise(cv::Size size, int color, cv::Size patch_size_ = cv::Size(8, 8));
	RedundantDXTDenoise();
	void operator()(cv::Mat& src, cv::Mat& dest, float sigma, cv::Size psize = cv::Size(8, 8), BASIS transform_basis = BASIS::DCT);

	//void shearable(cv::Mat& src, cv::Mat& dest, float sigma, cv::Size psize = cv::Size(8, 8), int transform_basis = 0, int direct = 0);
	//void weighted(cv::Mat& src, cv::Mat& dest, float sigma, cv::Size psize = cv::Size(8, 8), int transform_basis = 0);
	//void test(cv::Mat& src, cv::Mat& dest, float sigma, cv::Size psize = cv::Size(8, 8));

private:
	BASIS basis;
	cv::Size patch_size;
	cv::Size size;
	cv::Mat buff;
	cv::Mat sum;

	cv::Mat im;

	int channel;

	void body(float *src, float* dest, float Th);
	void body(float *src, float* dest, float* wmap, float Th);
	void body(float *src, float* dest, float Th, int dr);

	void div(float* inplace0, float* inplace1, float* inplace2, float* w0, float* w1, float* w2, const int size1);
	void div(float* inplace0, float* inplace1, float* inplace2, const int patch_area, const int size1);

	void div(float* inplace0, float* w0, const int size1);
	void div(float* inplace0, const int patch_area, const int size1);

	void decorrelateColorForward(float* src, float* dest, int width, int height);
	void decorrelateColorInvert(float* src, float* dest, int width, int height);
};