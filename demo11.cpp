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

	// 1.��������ֵ,α�����߼�
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

	// 2.���������ֵ,α�����߼�,��3.jpg�෴
	/*if src(x, y) > thresh
		dst(x, y) = 0
	else
		dst(x, y) = maxValue*/
	// Thresholding using THRESH_BINARY_INV 
	threshold(src, dst, 127, 255, THRESH_BINARY_INV);
	imwrite("Resources/thresh/4.jpg", dst);

	// 3.�ض���ֵ
	/*if src(x, y) > thresh
		dst(x, y) = thresh
	else
		dst(x, y) = src(x, y)*/
	// Thresholding using THRESH_TRUNC 
	threshold(src, dst, 127, 255, THRESH_TRUNC);
	imwrite("Resources/thresh/5.jpg", dst);

	// 4.��ֵΪ��
	/*if src(x, y) > thresh
		dst(x, y) = src(x, y)
	else
		dst(x, y) = 0*/
	// Thresholding using THRESH_TOZERO 
	threshold(src, dst, 127, 255, THRESH_TOZERO);
	imwrite("Resources/thresh/6.jpg", dst);

	// 5.������ֵΪ��
	/*if src(x, y) > thresh
		dst(x, y) = 0
	else
		dst(x, y) = src(x, y)*/
	// Thresholding using THRESH_TOZERO_INV 
	threshold(src, dst, 127, 255, THRESH_TOZERO_INV);
	imwrite("Resources/thresh/7.jpg", dst);
	return 0;
}