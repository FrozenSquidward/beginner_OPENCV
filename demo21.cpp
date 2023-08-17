#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;


// 基于模型匹配 matchMethod
// 它只能进行平行移动，若原图像中的匹配目标发生旋转或大小变化，该算法无效。
int demo21() {
    // 1.0 该方法可以识别相同的图片
	Mat imageA, imageB;// 目标图，原图
	imageA = imread("Resources/bb.png");
	imageB = imread("Resources/aa.jpeg");
    if (imageA.empty() || imageB.empty()) {
        std::cout << "无法读取图像" << std::endl;
        return -1;
    }
    // 使用模板匹配找到 B 中与 A 相似的区域
    cv::Mat result;
    int matchMethod = cv::TM_CCOEFF_NORMED;
    cv::matchTemplate(imageB, imageA, result, matchMethod);
    double minVal, maxVal;
    cv::Point minLoc, maxLoc;
    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
    // 在 B 上绘制相似区域的矩形框
    cv::Rect similarRegion(maxLoc, cv::Size(imageA.cols, imageA.rows));
    cv::rectangle(imageB, similarRegion, cv::Scalar(0, 0, 255), 2);
    // 对相似区域进行处理（这里只是简单地将其转为灰度）
    cv::Mat processedRegion = imageB(similarRegion);
    cv::cvtColor(processedRegion, processedRegion, cv::COLOR_BGR2GRAY);
    // 显示结果
    namedWindow("Processed Image B", 0);
    resizeWindow("Processed Image B", 640, 480);
    cv::imshow("Processed Image B", imageB);

	waitKey(0);
	return 0;
}