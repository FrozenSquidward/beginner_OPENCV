// ѧϰ��ַ�� https://learnopencv.com/read-display-and-write-an-image-using-opencv/
#include<opencv2/opencv.hpp>
#include<iostream>

// Namespace nullifies the use of cv::function(); 
using namespace std;
using namespace cv;

// 1.Read an image 
//Ҫ��ȡͼ����ʹ�� OpenCV �еĺ������﷨���£�imread()
//imread(filename, flags)
//����Ҫ����������
//��һ��������ͼ�����ƣ�����Ҫ�ļ�����ȫ�޶�·������
//�ڶ���������һ����ѡ��־������ָ��Ӧ��α�ʾͼ��OpenCVΪ�˱�־�ṩ�˼���ѡ��������ѡ�������
//cv2.IMREAD_UNCHANGED�� - 1
//cv2.IMREAD_GRAYSCALE��0
//cv2.IMREAD_COLOR��1
//Mat img_grayscale = imread("C:\\Users\\dell\\Desktop\\test.jpg", 1);
Mat img_color = imread("Resources/test.jpg", IMREAD_COLOR);
Mat img_grayscale = imread("Resources/test.jpg", IMREAD_GRAYSCALE);
Mat img_unchanged = imread("Resources/test.jpg", IMREAD_UNCHANGED);

void demo3() {
	// 2.Display the image.
	//�˺�������������������
	//��һ�������ǽ��ڴ�������ʾ�Ĵ������ơ�
	//�ڶ���������Ҫ��ʾ��ͼ��
	imshow("color image", img_color);
	// 3.Ҫһ����ʾ���ͼ����ΪҪ��ʾ��ÿ��ͼ��ָ���µĴ������ơ�
	imshow("grayscale image", img_grayscale);
	imshow("unchanged image", img_unchanged);

	// 4.Wait for a keystroke.   
	waitKey(0);

	// 5.Destroys all the windows created                         
	destroyAllWindows();

	// 6.Write the image in the same directory
	//��дӳ��
	//��һ���������ļ���������������ļ���չ�������� .png��.jpg �ȣ���OpenCV ʹ�ô��ļ���չ����ָ���ļ��ĸ�ʽ��
	//�ڶ���������Ҫ�����ͼ�����ͼ�񱣴�ɹ����ú��������ء�True
	imwrite("Resources/grayscale.jpg", img_grayscale);
}