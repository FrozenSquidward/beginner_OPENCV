// https://learnopencv.com/contour-detection-using-opencv-python-c/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// ÂÖÀª¼ì²â
int demo15() 
{
	Mat image = imread("Resources/test.jpg");

	Mat img_gray;
	cvtColor(image, img_gray, COLOR_BGR2GRAY);

	// apply binary thresholding
	Mat thresh;
	threshold(img_gray, thresh, 150, 255, THRESH_BINARY);
	/*imshow("Binary mage", thresh);
	waitKey(0);*/
	//imwrite("Resources/image_thres1.jpg", thresh);

	// detect the contours on the binary image using cv2.CHAIN_APPROX_NONE
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(thresh, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
	// draw contours on the original image
	Mat image_copy = image.clone();
	drawContours(image_copy, contours, -1, Scalar(0, 255, 0), 2);
	imshow("None approximation", image_copy);
	waitKey(0);
	//imwrite("Resources/contours_none_image1.jpg", image_copy);
	destroyAllWindows();

	//...¿´ÂéÁË£¬Ãþ»áÓã
	return 10;
}