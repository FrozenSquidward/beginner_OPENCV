// https://learnopencv.com/blob-detection-using-opencv-python-c/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


// °ßµã¼ì²âÆ÷ £¿£¿£¿
int demo12() 
{
	// Read image
	Mat im = imread("Resources/BlobTest.jpg", IMREAD_GRAYSCALE);
	imshow("im", im);

	// Detect blobs.
	std::vector<KeyPoint> keypoints;

	// Setup SimpleBlobDetector parameters.
	SimpleBlobDetector::Params params;
	// Change thresholds
	params.minThreshold = 10;
	params.maxThreshold = 200;
	// Filter by Area.
	params.filterByArea = true;
	params.minArea = 1500;
	// Filter by Circularity
	params.filterByCircularity = true;
	params.minCircularity = 0.1;
	// Filter by Convexity
	params.filterByConvexity = true;
	params.minConvexity = 0.87;
	// Filter by Inertia
	params.filterByInertia = true;
	params.minInertiaRatio = 0.01;
#if CV_MAJOR_VERSION < 3   // If you are using OpenCV 2
	// Set up detector with params
	SimpleBlobDetector detector(params);
	// You can use the detector this way
	// detector.detect( im, keypoints);
#else
	// Set up detector with params
	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);
	// SimpleBlobDetector::create creates a smart pointer. 
	// So you need to use arrow ( ->) instead of dot ( . )
	detector->detect( im, keypoints);
#endif
	// Draw detected blobs as red circles.
	// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
	Mat im_with_keypoints;
	drawKeypoints(im, keypoints, im_with_keypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	 // Show blobs
	imshow("keypoints", im_with_keypoints);
	waitKey(0);
	return 0;
}