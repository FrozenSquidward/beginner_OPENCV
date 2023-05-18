// https://learnopencv.com/image-filtering-using-convolution-in-opencv/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// 使用卷积进行图像过滤
int demo10() 
{
    // Read Image
    Mat image = imread("Resources/wood.jpg");

    // Print Error message if image is null
    if (image.empty())
    {
        cout << "Could not read image" << endl;
    }

    // Apply identity filter using kernel
    Mat kernel1 = (Mat_<double>(3, 3) << 0, 0, 0, 
                                         0, 1, 0, 
                                         0, 0, 0);
    Mat identity;
    filter2D(image, identity, -1, kernel1, Point(-1, -1), 0, 4);
    imshow("Original", image);
    imshow("Identity", identity);
    waitKey();
    imwrite("Resources/wood2identity.jpg", identity);
    destroyAllWindows();

    // Blurred using kernel
    // Initialize matrix with all ones
    Mat kernel2 = Mat::ones(5, 5, CV_64F);
    // Normalize the elements
    kernel2 = kernel2 / 25;
    Mat img;
    filter2D(image, img, -1, kernel2, Point(-1, -1), 0, 4);
    imshow("Original", image);
    imshow("Kernel blur", img);
    imwrite("Resources/wood2blur_kernel.jpg", img);
    waitKey();
    destroyAllWindows();

	return 0;
}

// 内置函数模糊图像,本质上是一个方便的功能
int demo10_1()
{
    Mat image = imread("Resources/wood.jpg");
    // Blurred using OpenCV C++ blur() function
    Mat img_blur;
    blur(image, img_blur, Size(5, 5));
    imshow("Original", image);
    imshow("Blurred", img_blur);
    //imwrite("Resources/wood2blur.jpg", img_blur);
    waitKey();
    destroyAllWindows();
    return 0;
}

//高斯模糊
int demo10_2()
{
    Mat image = imread("Resources/wood.jpg");
    // Performing Gaussian Blur
    Mat gaussian_blur;
    GaussianBlur(image, gaussian_blur, Size(5, 5), 0, 0);
    imshow("Original", image);
    imshow("Gaussian Blurred", gaussian_blur);
    //imwrite("Resources/gaussian_blur.jpg", gaussian_blur);
    waitKey();
    destroyAllWindows();
    return 0;
}

// 中位数模糊。在中值模糊中，源图像中的每个像素都替换为内核区域中图像像素的中值。
// 请注意，对于相同的内核大小，中值模糊的效果比高斯模糊更突出。中位数毛刺通常用于减少图像中的“盐和胡椒”噪声
int demo10_3()
{
    Mat image = imread("Resources/wood.jpg");
    // Performing Gaussian Blur
    Mat median_blur;
    medianBlur(image, median_blur, (5, 5));
    imshow("Original", image);
    imshow("Median Blurred", median_blur);
    //imwrite("Resources/median_blur.jpg", gaussian_blur);
    waitKey();
    destroyAllWindows();
    return 0;
}

// 使用自定义 2D 卷积内核锐化图像
int demo10_4()
{
    Mat image = imread("Resources/wood.jpg");

    // Apply sharpening using kernel
    Mat sharp_img;
    Mat kernel3 = (Mat_<double>(3, 3) << 0, -1, 0,
                                        -1, 5, -1,
                                        0, -1, 0);
    filter2D(image, sharp_img, -1, kernel3, Point(-1, -1), 0, BORDER_DEFAULT);
    imshow("Original", image);
    imshow("Sharpenned", sharp_img);
    //imwrite("Resources/sharp_image.jpg", sharp_img);
    waitKey();
    destroyAllWindows();
    return 0;
}

// 对图像应用双边滤波,对硬件要求较高
int demo10_5()
{
    Mat image = imread("Resources/wood.jpg");

    // Apply bilateral filtering
    Mat bilateral_filter;
    bilateralFilter(image, bilateral_filter, 9, 75, 75);
    imshow("Original", image);
    imshow("Bilateral filtering", bilateral_filter);
    //imwrite("Resources/bilateral_filtering.jpg", bilateral_filter);
    waitKey(0);
    destroyAllWindows();
    return 0;
}