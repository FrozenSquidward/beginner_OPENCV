// https://learnopencv.com/edge-detection-using-opencv/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// 边缘检测
int demo13() 
{
    // Reading image
    Mat img = imread("Resources/test.jpg");
    // Display original image
    imshow("original Image", img);
    waitKey(0);

    // Convert to graycsale
    Mat img_gray;
    cvtColor(img, img_gray, COLOR_BGR2GRAY);
    // Blur the image for better edge detection
    Mat img_blur;
    GaussianBlur(img_gray, img_blur, Size(3, 3), 0);

    //// Sobel edge detection
    //Mat sobelx, sobelx2, sobely, sobelxy;
    //Sobel(img_blur, sobelx, CV_64F, 1, 0, 5);
    //Sobel(img_blur, sobelx2, CV_64F, 2, 0, 5);
    //Sobel(img_blur, sobely, CV_64F, 0, 1, 5);
    //Sobel(img_blur, sobelxy, CV_64F, 1, 1, 5);
    //// Display Sobel edge detection images
    //imshow("Sobel X", sobelx);
    //imshow("Sobel X2", sobelx);
    //waitKey(0);
    //imshow("Sobel Y", sobely);
    //waitKey(0);
    //imshow("Sobel XY using Sobel() function", sobelxy);
    //waitKey(0);

    // Canny edge detection
    Mat edges, edges2,edges3, edges4;
    Canny(img_blur, edges, 100, 200, 3, false);
    Canny(img, edges4, 100, 200, 3, false);
    // Display canny edge detected image
    imshow("Canny edge detection", edges);
    /*Canny(img_blur, edges2, 150, 200, 3, false);//通道阈值越窄，描述越少
    Canny(img_blur, edges3, 190, 200, 3, false);
    imshow("2", edges2);
    imshow("3", edges3);*/
    imshow("4", edges4);//噪音多
    waitKey(0);

    destroyAllWindows();
	return 0;
}