#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int demo11()
{
	// Read image 
	Mat src = imread("Resources/thresh/input_image.jpg", IMREAD_GRAYSCALE);
	/*imshow("src", src);
	waitKey();*/
	Mat dst;

	// 1.二进制阈值,伪代码逻辑
	/*if src(x, y) > thresh
		dst(x, y) = maxValue
	else
		dst(x, y) = 0*/
	// Basic threhold example 
	threshold(src, dst, 0, 255, THRESH_BINARY);
	imwrite("Resources/thresh/1.jpg", dst);

	// Thresholding with maxval set to 128
	threshold(src, dst, 0, 128, THRESH_BINARY);
	imwrite("Resources/thresh/2.jpg", dst);

	// Thresholding with threshold value set 127 
	threshold(src, dst, 127, 255, THRESH_BINARY);
	imwrite("Resources/thresh/3.jpg", dst);

	// 2.逆二进制阈值,伪代码逻辑,与3.jpg相反
	/*if src(x, y) > thresh
		dst(x, y) = 0
	else
		dst(x, y) = maxValue*/
	// Thresholding using THRESH_BINARY_INV 
	threshold(src, dst, 127, 255, THRESH_BINARY_INV);
	imwrite("Resources/thresh/4.jpg", dst);

	// 3.截断阈值
	/*if src(x, y) > thresh
		dst(x, y) = thresh
	else
		dst(x, y) = src(x, y)*/
	// Thresholding using THRESH_TRUNC 
	threshold(src, dst, 127, 255, THRESH_TRUNC);
	imwrite("Resources/thresh/5.jpg", dst);

	// 4.阈值为零
	/*if src(x, y) > thresh
		dst(x, y) = src(x, y)
	else
		dst(x, y) = 0*/
	// Thresholding using THRESH_TOZERO 
	threshold(src, dst, 127, 255, THRESH_TOZERO);
	imwrite("Resources/thresh/6.jpg", dst);

	// 5.倒置阈值为零
	/*if src(x, y) > thresh
		dst(x, y) = 0
	else
		dst(x, y) = src(x, y)*/
	// Thresholding using THRESH_TOZERO_INV 
	threshold(src, dst, 127, 255, THRESH_TOZERO_INV);
	imwrite("Resources/thresh/7.jpg", dst);
	return 0;
}