// https://learnopencv.com/image-rotation-and-translation-using-opencv/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// ����ͼ����ת��ת��
int demo7() 
{
    Mat image = imread("Resources/test.jpg");
    imshow("image", image);
    /*waitKey(0);*/
    double angle = 45;

    // 1.�����ת����
    // get the center coordinates of the image to create the 2D rotation matrix
    Point2f center((image.cols - 1) / 2.0, (image.rows - 1) / 2.0);
    // using getRotationMatrix2D() to get the rotation matrix
    /* 2.���� 2D ��ת����
      center������ͼ�����ת����
      angle���Զ�Ϊ��λ����ת�Ƕ� ��������ͼ������ʱ�뷽����ת����������ͼ��˳ʱ����ת��
      scale�������ṩ��ֵ���ϻ���������ͼ��ĸ���ͬ�Ա�������(�Ŵ�^��С)*/
    Mat rotation_matix = getRotationMatrix2D(center, angle, 0.5);

    // we will save the resulting image in rotated_image matrix
    // 3.������任Ӧ����ͼ
    Mat rotated_image;

    cout << "size : " << image.size() << endl;
    // rotate the image using warpAffine
    warpAffine(image, rotated_image, rotation_matix, image.size());
    imshow("Rotated image", rotated_image);
    // wait indefinitely, press any key on keyboard to exit
    waitKey(0);
    // save the rotated image to disk
    imwrite("Resources/rotated_im.jpg", rotated_image);

    return 0;
}

// ����ͼ��??
int demo7_1()
{
    Mat image = imread("Resources/test.jpg");
    int h = image.size().height;
    int w = image.size().width;

    // get tx and ty values for translation
    float ty = (float)h / 4;
    float tx = (float)w / 4;

    // create the translation matrix using tx and ty
    float warp_values[] = { 1.0, 0.0, tx, 0.0, 1.0, ty };
    Mat translation_matrix = Mat(2, 3, CV_32F, warp_values);

    // save the resulting image in translated_image matrix
    Mat translated_image;
    // apply affine transformation to the original image using the translation matrix
    warpAffine(image, translated_image, translation_matrix, image.size());

    //display the original and the Translated images
    imshow("Translated image", translated_image);
    imshow("Original image", image);
    waitKey(0);
    // save the translated image to disk
    imwrite("Resources/translated_image.jpg", translated_image);
    return 0;
}