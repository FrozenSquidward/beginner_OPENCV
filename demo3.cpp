// 学习网址： https://learnopencv.com/read-display-and-write-an-image-using-opencv/
#include<opencv2/opencv.hpp>
#include<iostream>

// Namespace nullifies the use of cv::function(); 
using namespace std;
using namespace cv;

// 1.Read an image 
//要读取图像，请使用 OpenCV 中的函数。语法如下：imread()
//imread(filename, flags)
//它需要两个参数：
//第一个参数是图像名称，它需要文件的完全限定路径名。
//第二个参数是一个可选标志，用于指定应如何表示图像。OpenCV为此标志提供了几个选项，但最常见的选项包括：
//cv2.IMREAD_UNCHANGED或 - 1
//cv2.IMREAD_GRAYSCALE或0
//cv2.IMREAD_COLOR或1
//Mat img_grayscale = imread("C:\\Users\\dell\\Desktop\\test.jpg", 1);
Mat img_color = imread("Resources/test.jpg", IMREAD_COLOR);
Mat img_grayscale = imread("Resources/test.jpg", IMREAD_GRAYSCALE);
Mat img_unchanged = imread("Resources/test.jpg", IMREAD_UNCHANGED);

void demo3() {
	// 2.Display the image.
	//此函数还接受两个参数：
	//第一个参数是将在窗口上显示的窗口名称。
	//第二个参数是要显示的图像。
	imshow("color image", img_color);
	// 3.要一次显示多个图像，请为要显示的每个图像指定新的窗口名称。
	imshow("grayscale image", img_grayscale);
	imshow("unchanged image", img_unchanged);

	// 4.Wait for a keystroke.   
	waitKey(0);

	// 5.Destroys all the windows created                         
	destroyAllWindows();

	// 6.Write the image in the same directory
	//编写映像
	//第一个参数是文件名，它必须包含文件扩展名（例如 .png、.jpg 等）。OpenCV 使用此文件扩展名来指定文件的格式。
	//第二个参数是要保存的图像。如果图像保存成功，该函数将返回。True
	imwrite("Resources/grayscale.jpg", img_grayscale);
}