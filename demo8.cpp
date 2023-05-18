// https://learnopencv.com/annotating-images-using-opencv/
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// 注释图像
// 1.用颜色线为图像添加批注
int demo8_1() 
{
    // Read Images
    Mat img = imread("Resources/test.jpg");
    // Display Image
    /*imshow("Original Image", img);
    waitKey();*/
    // Print Error message if image is null
    if (img.empty())
    {
        cout << "Could not read image" << endl;
    }
    // 1.1 Draw line on image
    /*Mat imageLine = img.clone();
    Point pointA(200, 80);
    Point pointB(450, 180);
    line(imageLine, pointA, pointB, Scalar(255, 255, 0), 3, 8, 0);
    imshow("Lined Image", imageLine);*/
    // 1.2 画一个圆 （请注意，它只是圆的轮廓。）
    /*Mat imageCircle = img.clone();
    Point2f center((imageCircle.cols - 1) / 2.0, (imageCircle.rows - 1) / 2.0);
    circle(imageCircle, center, imageCircle.cols/5, Scalar(0, 0, 255), 1);
    imshow("imageCircle", imageCircle);*/
    // 1.3 绘制实心圆 厚度参数更改为-1
    /*Mat imageCircle = img.clone();
    Point2f center((imageCircle.cols - 1) / 2.0, (imageCircle.rows - 1) / 2.0);
    circle(imageCircle, center, imageCircle.cols / 5, Scalar(255, 0, 0), -1);
    imshow("imageCircle", imageCircle); */
    // 1.4 绘制矩形
    //Mat imageRectangle = img.clone();
    //Point start_point(380, 160);//起点（左上角）
    //Point end_point(640, 550);//终点（右下角）
    //rectangle(imageRectangle, start_point, end_point, Scalar(255, 0, 0), 1);
    //imshow("imageRectangle", imageRectangle);
    // 1.5 椭圆
    //Mat imageEllipse = img.clone();
    //Point2f center((imageEllipse.cols - 1) / 2.0, (imageEllipse.rows - 1) / 2.0);
    //Point axis1(100, 50);//定义长轴和短轴
    //Point axis2(125, 50);
    //ellipse(imageEllipse, center, axis1, 0, 0, 200, Scalar(255, 0, 0), -3);
    //ellipse(imageEllipse, center, axis2, 90, 180, 360, Scalar(0, 0, 255), 3);
    // 1.6 添加文本 中文乱码
    Mat imagePutText = img.clone();
    putText(imagePutText, "huahua", Point(50, 350), FONT_HERSHEY_COMPLEX, 1.5, Scalar(0, 255, 0));

    imshow("imagePutText", imagePutText);

    waitKey();
	return 0;
}