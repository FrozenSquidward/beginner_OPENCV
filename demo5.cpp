//https://learnopencv.com/image-resizing-with-opencv/
// let's start with including libraries 
#include<opencv2/opencv.hpp>
#include<iostream>

// Namespace to nullify use of cv::function(); syntax
using namespace std;
using namespace cv;

// 调整图像大小
int demo5()
{
	// Read the image using imread function
	Mat image = imread("Resources/test.jpg");

	// 1.通过指定宽度和高度调整大小
	//cout << "Original Height and Width :" << image.rows << "x" << image.cols << endl;//682x1024
	//int H = image.size().height;
	//int W = image.size().width;
	//cout << "源图片高：" << H << endl;//682
	//cout << "源图片宽" << W << endl;//1024
	//imshow("Original Image", image);
	//// let's downscale the image using new  width and height
	//int down_width = 300;
	//int down_height = 200;
	//Mat resized_down;
	////resize down
	//resize(image, resized_down, Size(down_width, down_height), INTER_LINEAR);
	//// let's upscale the image using new  width and height
	//int up_width = 600;
	//int up_height = 400;
	//Mat resized_up;
	////resize up
	//resize(image, resized_up, Size(up_width, up_height), INTER_LINEAR);
	//// Display Images and press any key to continue
	//imshow("Resized Down by defining height and width", resized_down);
	//imshow("Resized Up image by defining height and width", resized_up);
	//waitKey();

	//// 2.使用比例因子调整大小
	//// Scaling Up the image 1.2 times by specifying both scaling factors
	//double scale_up_x = 1.2;
	//double scale_up_y = 1.2;
	//// Scaling Down the image 0.6 times specifying a single scale factor.
	double scale_down = 2.2;
	//Mat scaled_f_up, scaled_f_down;
	////resize 
	//resize(image, scaled_f_down, Size(), scale_down, scale_down, INTER_LINEAR);
	//resize(image, scaled_f_up, Size(), scale_up_x, scale_up_y, INTER_LINEAR);
	//imshow("scale_up", scaled_f_up);
	//imshow("scale_down", scaled_f_down);
	//waitKey();

	// 3.使用不同的插值方法调整大小
	// Scaling Down the image 0.6 using different Interpolation Method
	Mat res_inter_linear, res_inter_nearest, res_inter_area;
	resize(image, res_inter_linear, Size(), scale_down, scale_down, INTER_LINEAR);
	resize(image, res_inter_nearest, Size(), scale_down, scale_down, INTER_NEAREST);
	resize(image, res_inter_area, Size(), scale_down, scale_down, INTER_AREA);
	/*imshow("1", res_inter_area);
	imshow("2", res_inter_nearest);
	imshow("3", res_inter_area);*/
	Mat a, b, c;
	// vconcat()函数用于实现图像或矩阵数据的上下连接，hconcat()函数用于实现图像或矩阵数据的左右连接。
	/*vconcat(res_inter_linear, res_inter_nearest, a);
	vconcat(res_inter_area, res_inter_area, b);
	vconcat(a, b, c);*/
	hconcat(res_inter_linear, res_inter_nearest, a);
	hconcat(res_inter_area, res_inter_area, b);
	hconcat(a, b, c);
	// Display the image Press any key to continue
	imshow("Inter Linear :: Inter Nearest :: Inter Area :: Inter Area", c);
	waitKey();
	// imwrite("Resources/hconcat.jpg",c);

	destroyAllWindows();
	return 0;
}