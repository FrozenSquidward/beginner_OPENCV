#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;


// ����ģ��ƥ�� matchMethod
// ��ֻ�ܽ���ƽ���ƶ�����ԭͼ���е�ƥ��Ŀ�귢����ת���С�仯�����㷨��Ч��
int demo21() {
    // 1.0 �÷�������ʶ����ͬ��ͼƬ
	Mat imageA, imageB;// Ŀ��ͼ��ԭͼ
	imageA = imread("Resources/bb.png");
	imageB = imread("Resources/aa.jpeg");
    if (imageA.empty() || imageB.empty()) {
        std::cout << "�޷���ȡͼ��" << std::endl;
        return -1;
    }
    // ʹ��ģ��ƥ���ҵ� B ���� A ���Ƶ�����
    cv::Mat result;
    int matchMethod = cv::TM_CCOEFF_NORMED;
    cv::matchTemplate(imageB, imageA, result, matchMethod);
    double minVal, maxVal;
    cv::Point minLoc, maxLoc;
    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);
    // �� B �ϻ�����������ľ��ο�
    cv::Rect similarRegion(maxLoc, cv::Size(imageA.cols, imageA.rows));
    cv::rectangle(imageB, similarRegion, cv::Scalar(0, 0, 255), 2);
    // ������������д�������ֻ�Ǽ򵥵ؽ���תΪ�Ҷȣ�
    cv::Mat processedRegion = imageB(similarRegion);
    cv::cvtColor(processedRegion, processedRegion, cv::COLOR_BGR2GRAY);
    // ��ʾ���
    namedWindow("Processed Image B", 0);
    resizeWindow("Processed Image B", 640, 480);
    cv::imshow("Processed Image B", imageB);

	waitKey(0);
	return 0;
}