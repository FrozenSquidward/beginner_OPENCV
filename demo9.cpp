// https://learnopencv.com/color-spaces-in-opencv-cpp-python/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// É«²Ê¿Õ¼ä ?????
int demo9() 
{
	Mat two_cubes = imread("Resources/two-cubes.png");
	imshow("two_cubes", two_cubes);

	Mat two_cubes2Lab;
	cvtColor(two_cubes, two_cubes2Lab, COLOR_BGR2Lab);
	Mat two_cubes2YCrCb;
	cvtColor(two_cubes, two_cubes2YCrCb, COLOR_BGR2YCrCb);
	Mat two_cubes2HSV;
	cvtColor(two_cubes, two_cubes2HSV, COLOR_BGR2HSV);

	imshow("Lab", two_cubes2Lab);
	imshow("YCrCb", two_cubes2YCrCb);
	imshow("HSV", two_cubes2HSV);
	/*imwrite("Resources/two_cubes2Lab", two_cubes2Lab);
	imwrite("Resources/two_cubes2YCrCb", two_cubes2YCrCb);
	imwrite("Resources/two_cubes2HSV", two_cubes2HSV);
	*/
	waitKey();
	return 0;
}

int demo9_1() 
{
	Mat two_cubes = imread("Resources/two-cubes.png");
	Mat two_cubes2Lab;
	cvtColor(two_cubes, two_cubes2Lab, COLOR_BGR2Lab);
	Mat two_cubes2YCrCb;
	cvtColor(two_cubes, two_cubes2YCrCb, COLOR_BGR2YCrCb);
	Mat two_cubes2HSV;
	cvtColor(two_cubes, two_cubes2HSV, COLOR_BGR2HSV);

	//C++ code
	cv::Vec3b bgrPixel(40, 158, 16);
	// Create Mat object from vector since cvtColor accepts a Mat object
	Mat3b bgr(bgrPixel);

	//Convert pixel values to other color spaces.
	Mat3b hsv, ycb, lab;
	cvtColor(bgr, ycb, COLOR_BGR2YCrCb);
	cvtColor(bgr, hsv, COLOR_BGR2HSV);
	cvtColor(bgr, lab, COLOR_BGR2Lab);
	//Get back the vector from Mat
	Vec3b hsvPixel(hsv.at<Vec3b>(0, 0));
	Vec3b ycbPixel(ycb.at<Vec3b>(0, 0));
	Vec3b labPixel(lab.at<Vec3b>(0, 0));

	int thresh = 40;

	cv::Scalar minBGR = cv::Scalar(bgrPixel.val[0] - thresh, bgrPixel.val[1] - thresh, bgrPixel.val[2] - thresh);
	cv::Scalar maxBGR = cv::Scalar(bgrPixel.val[0] + thresh, bgrPixel.val[1] + thresh, bgrPixel.val[2] + thresh);

	cv::Mat maskBGR, resultBGR;
	cv::inRange(two_cubes, minBGR, maxBGR, maskBGR);
	cv::bitwise_and(two_cubes, two_cubes, resultBGR, maskBGR);

	cv::Scalar minHSV = cv::Scalar(hsvPixel.val[0] - thresh, hsvPixel.val[1] - thresh, hsvPixel.val[2] - thresh);
	cv::Scalar maxHSV = cv::Scalar(hsvPixel.val[0] + thresh, hsvPixel.val[1] + thresh, hsvPixel.val[2] + thresh);

	cv::Mat maskHSV, resultHSV;
	cv::inRange(two_cubes2HSV, minHSV, maxHSV, maskHSV);
	cv::bitwise_and(two_cubes2HSV, two_cubes2HSV, resultHSV, maskHSV);

	cv::Scalar minYCB = cv::Scalar(ycbPixel.val[0] - thresh, ycbPixel.val[1] - thresh, ycbPixel.val[2] - thresh);
	cv::Scalar maxYCB = cv::Scalar(ycbPixel.val[0] + thresh, ycbPixel.val[1] + thresh, ycbPixel.val[2] + thresh);

	cv::Mat maskYCB, resultYCB;
	cv::inRange(two_cubes2YCrCb, minYCB, maxYCB, maskYCB);
	cv::bitwise_and(two_cubes2YCrCb, two_cubes2YCrCb, resultYCB, maskYCB);

	cv::Scalar minLAB = cv::Scalar(labPixel.val[0] - thresh, labPixel.val[1] - thresh, labPixel.val[2] - thresh);
	cv::Scalar maxLAB = cv::Scalar(labPixel.val[0] + thresh, labPixel.val[1] + thresh, labPixel.val[2] + thresh);

	cv::Mat maskLAB, resultLAB;
	cv::inRange(two_cubes2Lab, minLAB, maxLAB, maskLAB);
	cv::bitwise_and(two_cubes2Lab, two_cubes2Lab, resultLAB, maskLAB);

	imshow("Result maskBGR", maskBGR);
	imshow("Result BGR", resultBGR);

	/*imshow("Result HSV", resultHSV);
	imshow("Result YCB", resultYCB);
	imshow("Output LAB", resultLAB);*/
	waitKey();
	return 0;
}