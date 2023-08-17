#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace std;
using namespace cv;
using namespace xfeatures2d;

int demo22() {
	Mat imageA = imread("Resources/ab.png", IMREAD_GRAYSCALE);
	Mat imageB = imread("Resources/aa.jpeg", IMREAD_GRAYSCALE);

    if (imageA.empty() || imageB.empty()) {
        std::cout << "无法读取图像文件" << std::endl;
        return -1;
    }

    // 初始化SIFT检测器
    Ptr<SIFT> sift = SIFT::create();

    // 检测图像A中的关键点和描述符
    std::vector<KeyPoint> keypointsA;
    Mat descriptorsA;
    sift->detectAndCompute(imageA, noArray(), keypointsA, descriptorsA);

    // 检测图像B中的关键点和描述符
    std::vector<KeyPoint> keypointsB;
    Mat descriptorsB;
    sift->detectAndCompute(imageB, noArray(), keypointsB, descriptorsB);

    // 使用FLANN进行特征匹配
    FlannBasedMatcher matcher;
    std::vector<DMatch> matches;
    matcher.match(descriptorsA, descriptorsB, matches);

    // 筛选出最佳匹配
    double max_dist = 0;
    double min_dist = 100;
    for (int i = 0; i < descriptorsA.rows; i++) {
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }

    // 定义一个阈值，筛选出好的匹配
    std::vector<DMatch> good_matches;
    for (int i = 0; i < descriptorsA.rows; i++) {
        if (matches[i].distance <= std::max(2 * min_dist, 0.02)) {
            good_matches.push_back(matches[i]);
        }
    }

    // 绘制匹配结果
    Mat match_image;
    drawMatches(imageA, keypointsA, imageB, keypointsB, good_matches, match_image);

    // 在图像B中绘制框选的区域
    for (const auto& match : good_matches) {
        Point2f imgB_point = keypointsB[match.trainIdx].pt;
        rectangle(imageB, imgB_point - Point2f(50, 50), imgB_point + Point2f(50, 50), Scalar(0, 255, 0), 2);
    }

    // 显示结果
    namedWindow("Matches", 0);
    resizeWindow("Matches", 640, 480);
    imshow("Matches", match_image);

    namedWindow("Image B with Boxes", 0);
    resizeWindow("Image B with Boxes", 640, 480);
    imshow("Image B with Boxes", imageB);

    waitKey(0);
	return 0;
}

// 对图像A 背景过滤和预处理 ？？ 效果不好不能识别出物品
// 到这里可能已经到了识别极限了，下面考虑深度学习
int demo22_1() {
    // 读取图像A
    Mat imageA = imread("Resources/ab.png");

    if (imageA.empty()) {
        std::cout << "无法读取图像文件" << std::endl;
        return -1;
    }

    // 进行背景过滤和预处理
    Mat grayImageA;
    cvtColor(imageA, grayImageA, COLOR_BGR2GRAY);

    // 使用简单的阈值分割方法来提取物体
    Mat binaryImageA;
    threshold(grayImageA, binaryImageA, 150, 255, THRESH_BINARY);

    // 查找物体的轮廓
    std::vector<std::vector<Point>> contours;
    findContours(binaryImageA, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 找到最大的轮廓
    double maxArea = 0;
    int maxAreaIdx = -1;
    for (size_t i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        if (area > maxArea) {
            maxArea = area;
            maxAreaIdx = static_cast<int>(i);
        }
    }

    // 创建一个空白的黑色图像
    Mat processedImageA = Mat::zeros(imageA.size(), CV_8UC3);

    // 绘制找到的物体轮廓在空白图像上
    if (maxAreaIdx != -1) {
        drawContours(processedImageA, contours, maxAreaIdx, Scalar(255, 255, 255), FILLED);
    }

    // 显示处理后的图像A
    imshow("Processed Image A", processedImageA);
    waitKey(0);
    return 0;
}