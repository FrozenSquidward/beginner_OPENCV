#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
/*
摄像头人脸追踪
*/
CascadeClassifier faceDetector;
String haar_data_file = "D:\\opencv\\path\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt2.xml";
//https://zhuanlan.zhihu.com/p/100217697
int demo2() {
	Mat frame, gray;
	vector<Rect> faces;
	VideoCapture capture(0);
	faceDetector.load(haar_data_file);
	namedWindow("frame", WINDOW_AUTOSIZE);
	while (true) {
		capture.read(frame);
		flip(frame, frame, 1);//镜像一下，
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		equalizeHist(gray, gray);//增强一下对比度（还记得Haar的特征吗？黑白分明可以提高检测精度）
		faceDetector.detectMultiScale(gray, faces, 1.2, 1, 0, Size(30, 30), Size(300, 300));
		for (size_t t = 0; t < faces.size(); t++) {
			rectangle(frame, faces[t], Scalar(0, 0, 255), 2, 8, 0);
		}
		char c = waitKey(10);
		if (c == 27) {
			return 0;
		}
		imshow("frame", frame);
	}

	waitKey(0);
	return 0;
}


//https://blog.csdn.net/qq_27278957/article/details/108224325 
//缺少下面两个依赖尝试添加额为依赖,cv版本为460，额外依赖是470不知道冲突吗，CMAKE卡住了... 
//版本不一致不行，重新下了460扩展，执行第二部CMAKE，ok

// https://github.com/spmallick/learnopencv/tree/master/FacialLandmarkDetection 特别多的源码
// https://zhuanlan.zhihu.com/p/35390012 人脸关键点检测（FaceMark）
