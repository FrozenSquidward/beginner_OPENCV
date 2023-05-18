// https://learnopencv.com/mouse-and-trackbar-in-opencv-gui/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// Points to store the bounding box coordinates
Point top_left_corner, bottom_right_corner;
// image image
Mat image;

// function which will be called on mouse input
void drawRectangle(int action, int x, int y, int flags, void* userdata)
{
    cout << "action : " << action;
    // Mark the top left corner when left mouse button is pressed
    if (action == EVENT_LBUTTONDOWN)
    {
        top_left_corner = Point(x, y);
    }
    // When left mouse button is released, mark bottom right corner
    else if (action == EVENT_LBUTTONUP)
    {
        bottom_right_corner = Point(x, y);
        // Draw rectangle
        rectangle(image, top_left_corner, bottom_right_corner, Scalar(0, 255, 0), 2, 8);
        // Display image
        imshow("Window", image);
    }

}

// GUI 中的鼠标和跟踪栏
int demo14() 
{
    image = imread("Resources/test.jpg");
    // Make a temporary image, which will be used to clear the image
    Mat temp = image.clone();
    // Create a named window
    namedWindow("Window", WINDOW_NORMAL);
    // highgui function called when mouse events occur
    setMouseCallback("Window", drawRectangle);

    int k = 0;
    // loop until q character is pressed 退出
    while (k != 113)
    {
        imshow("Window", image);
        k = waitKey(0);
        cout << "k : " << k;
        // If c is pressed, clear the window, using the dummy image 重置为原始图像
        if (k == 99)
        {
            temp.copyTo(image);
        }
    }
    destroyAllWindows();
    return 0;
}

int maxScaleUp = 100;
int scaleFactor = 1; //用于我们将要定义的用于缩放图像的回调函数。

string windowName = "Resize Image";
string trackbarValue = "Scale";

// Callback functions
void scaleImage(int, void*)
{
    // Read the image
    Mat image = imread("Resources/test.jpg");

    cout << "scaleFactor : " << scaleFactor;
    // Get the Scale factor from the trackbar
    double scaleFactorDouble = 1 + scaleFactor / 100.0;

    // Set the factor to 1 if becomes 0
    if (scaleFactorDouble == 0)
    {
        scaleFactorDouble = 1;
    }

    Mat scaledImage;
    // Resize the image
    resize(image, scaledImage, Size(), scaleFactorDouble, scaleFactorDouble, INTER_LINEAR);
    // Display the image
    imshow(windowName, scaledImage);
}

int demo14_1() 
{
    // load an image
    Mat image = imread("Resources/test.jpg");

    // Create a window to display results and set the flag to Autosize
    namedWindow(windowName, WINDOW_AUTOSIZE);

    // Create Trackbars and associate a callback function
    // &scaleFactor 这里 &实际上函数指针声明
    createTrackbar(trackbarValue, windowName, &scaleFactor, maxScaleUp, scaleImage);
    scaleImage(25, 0);

    // Display image
    imshow(windowName, image);
    waitKey(0);
    destroyAllWindows();
    return 0;
}