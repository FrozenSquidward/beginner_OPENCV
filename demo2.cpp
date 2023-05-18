#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
/*
����ͷ����׷��
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
		flip(frame, frame, 1);//����һ�£�
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		equalizeHist(gray, gray);//��ǿһ�¶Աȶȣ����ǵ�Haar�������𣿺ڰ׷���������߼�⾫�ȣ�
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
//ȱ��������������������Ӷ�Ϊ����,cv�汾Ϊ460������������470��֪����ͻ��CMAKE��ס��... 
//�汾��һ�²��У���������460��չ��ִ�еڶ���CMAKE��ok

// https://github.com/spmallick/learnopencv/tree/master/FacialLandmarkDetection �ر���Դ��
// https://zhuanlan.zhihu.com/p/35390012 �����ؼ����⣨FaceMark��
