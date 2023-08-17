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
        std::cout << "�޷���ȡͼ���ļ�" << std::endl;
        return -1;
    }

    // ��ʼ��SIFT�����
    Ptr<SIFT> sift = SIFT::create();

    // ���ͼ��A�еĹؼ����������
    std::vector<KeyPoint> keypointsA;
    Mat descriptorsA;
    sift->detectAndCompute(imageA, noArray(), keypointsA, descriptorsA);

    // ���ͼ��B�еĹؼ����������
    std::vector<KeyPoint> keypointsB;
    Mat descriptorsB;
    sift->detectAndCompute(imageB, noArray(), keypointsB, descriptorsB);

    // ʹ��FLANN��������ƥ��
    FlannBasedMatcher matcher;
    std::vector<DMatch> matches;
    matcher.match(descriptorsA, descriptorsB, matches);

    // ɸѡ�����ƥ��
    double max_dist = 0;
    double min_dist = 100;
    for (int i = 0; i < descriptorsA.rows; i++) {
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }

    // ����һ����ֵ��ɸѡ���õ�ƥ��
    std::vector<DMatch> good_matches;
    for (int i = 0; i < descriptorsA.rows; i++) {
        if (matches[i].distance <= std::max(2 * min_dist, 0.02)) {
            good_matches.push_back(matches[i]);
        }
    }

    // ����ƥ����
    Mat match_image;
    drawMatches(imageA, keypointsA, imageB, keypointsB, good_matches, match_image);

    // ��ͼ��B�л��ƿ�ѡ������
    for (const auto& match : good_matches) {
        Point2f imgB_point = keypointsB[match.trainIdx].pt;
        rectangle(imageB, imgB_point - Point2f(50, 50), imgB_point + Point2f(50, 50), Scalar(0, 255, 0), 2);
    }

    // ��ʾ���
    namedWindow("Matches", 0);
    resizeWindow("Matches", 640, 480);
    imshow("Matches", match_image);

    namedWindow("Image B with Boxes", 0);
    resizeWindow("Image B with Boxes", 640, 480);
    imshow("Image B with Boxes", imageB);

    waitKey(0);
	return 0;
}

// ��ͼ��A �������˺�Ԥ���� ���� Ч�����ò���ʶ�����Ʒ
// ����������Ѿ�����ʶ�����ˣ����濼�����ѧϰ
int demo22_1() {
    // ��ȡͼ��A
    Mat imageA = imread("Resources/ab.png");

    if (imageA.empty()) {
        std::cout << "�޷���ȡͼ���ļ�" << std::endl;
        return -1;
    }

    // ���б������˺�Ԥ����
    Mat grayImageA;
    cvtColor(imageA, grayImageA, COLOR_BGR2GRAY);

    // ʹ�ü򵥵���ֵ�ָ������ȡ����
    Mat binaryImageA;
    threshold(grayImageA, binaryImageA, 150, 255, THRESH_BINARY);

    // �������������
    std::vector<std::vector<Point>> contours;
    findContours(binaryImageA, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // �ҵ���������
    double maxArea = 0;
    int maxAreaIdx = -1;
    for (size_t i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        if (area > maxArea) {
            maxArea = area;
            maxAreaIdx = static_cast<int>(i);
        }
    }

    // ����һ���հ׵ĺ�ɫͼ��
    Mat processedImageA = Mat::zeros(imageA.size(), CV_8UC3);

    // �����ҵ������������ڿհ�ͼ����
    if (maxAreaIdx != -1) {
        drawContours(processedImageA, contours, maxAreaIdx, Scalar(255, 255, 255), FILLED);
    }

    // ��ʾ������ͼ��A
    imshow("Processed Image A", processedImageA);
    waitKey(0);
    return 0;
}