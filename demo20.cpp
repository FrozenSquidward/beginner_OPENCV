#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

// 解决xfeatures2d依赖不存在的问题 
// https://blog.csdn.net/weixin_40649372/article/details/124979958

// 样例1:https://blog.csdn.net/Daker_Huang/article/details/84574671
// 样例2:https://cloud.tencent.com/developer/article/1997345
int demo20(){
	int64 t1, t2;
	double tkpt, tdes, tmatch_bf, tmatch_knn;
	Mat src1, src2;// 目标图，原图
	// 1.目标特征提取
	src1 = imread("Resources/ab.png",0);
	src2 = imread("Resources/aa.jpeg", 0);
	if (!src1.data)
	{
		cout << "图片未找到" << endl;
		return -1;
	}
	// imshow("灰度图", src1);

	int numfeature = 20000; // ???看起来是提高识别精准度但2k和2w好像没什么区别，但是200就只剩一个识别点了
	Ptr<SIFT> detector = SIFT::create(numfeature);//与SURF一样，剩余的取默认值？？？
	// 2计算特征点
	vector<KeyPoint> keypoints1;
	vector<KeyPoint> keypoints2;
	detector->detect(src1, keypoints1, Mat());
	detector->detect(src2, keypoints2, Mat());
	/*Mat resultImg1, resultImg2;
	drawKeypoints(src1, keypoints1, resultImg1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(src2, keypoints2, resultImg2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	imshow("SIFT图1", resultImg1);
	imshow("SIFT图2", resultImg2);*/
	t1 = cv::getTickCount();
	t2 = cv::getTickCount();


	// 3. 计算特征描述符
	cv::Mat descriptors1, descriptors2;
	t1 = cv::getTickCount();
	detector->compute(src1, keypoints1, descriptors1);
	t2 = cv::getTickCount();
	tdes = 1000.0 * (t2 - t1) / cv::getTickFrequency();
	detector->compute(src2, keypoints2, descriptors2);

	// 4. 特征匹配
	cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::BRUTEFORCE);
	// cv::BFMatcher matcher(cv::NORM_L2);

	// (1) 直接暴力匹配
	//std::vector<cv::DMatch> matches;
	//t1 = cv::getTickCount();
	//matcher->match(descriptors1, descriptors2, matches);
	//t2 = cv::getTickCount();
	//tmatch_bf = 1000.0 * (t2 - t1) / cv::getTickFrequency();
	//// 画匹配图
	//cv::Mat img_matches_bf;
	//drawMatches(src1, keypoints1, src2, keypoints2, matches, img_matches_bf);
	//imshow("bf_matches", img_matches_bf); // NB,但是看起来噪点比较多

	// (2) KNN-NNDR匹配法
	std::vector<std::vector<cv::DMatch> > knn_matches;
	const float ratio_thresh = 0.7f;
	std::vector<cv::DMatch> good_matches;
	t1 = cv::getTickCount();
	matcher->knnMatch(descriptors1, descriptors2, knn_matches, 2);
	for (auto& knn_matche : knn_matches) {
		if (knn_matche[0].distance < ratio_thresh * knn_matche[1].distance) {
			good_matches.push_back(knn_matche[0]);
		}
	}
	t2 = cv::getTickCount();
	tmatch_knn = 1000.0 * (t2 - t1) / cv::getTickFrequency();

	// 画匹配图
	cv::Mat img_matches_knn;
	drawMatches(src1, keypoints1, src2, keypoints2, good_matches, img_matches_knn, cv::Scalar::all(-1),
		cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	cv::imshow("knn_matches", img_matches_knn); // 噪点明显减少，但是过于少了

	waitKey(0);
	return 0;
}