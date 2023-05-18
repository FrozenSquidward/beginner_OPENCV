// Include Libraries
#include<opencv2/opencv.hpp>
#include<iostream>

// Namespace nullifies the use of cv::function();
using namespace std;
using namespace cv;

// 裁剪图像
int demo6()
{
	Mat img = imread("Resources/test2.png");

	// 1.尝试裁剪图像中包含花朵的部分。
	//Print the height and width of the image
	cout << "Width : " << img.size().width << endl;//500
	cout << "Height: " << img.size().height << endl;//333
	cout << "Channels: " << img.channels() << endl;//3
	// Display image
	imshow("Image", img);
	waitKey(0);
	// Slicing to crop the image
	Mat crop = img(Range(80, 280), Range(150, 330)); 
	// Display the cropped image
	imshow("Cropped Image", crop);
	waitKey(0);
	imwrite("Resources/crop.jpg", crop);

	destroyAllWindows();
	return 0;
}

// 2.使用裁剪将图像分割成小块
int demo6_1()
{
	Mat img = imread("Resources/test.jpg");
	Mat image_copy = img.clone();
	int imgheight = img.rows;   //682
	int imgwidth = img.cols;    //1024
    cout << "imgheight * imgwidth : " << imgheight << "*" << imgwidth << endl;
    int M = imgheight/3;
    int N = imgwidth/3;

    int x1 = 0;
    int y1 = 0;
    for (int y = 0; y < imgheight; y = y + M)
    {
        for (int x = 0; x < imgwidth; x = x + N)
        {
            if ((imgheight - y) < M || (imgwidth - x) < N)
            {
                break;
            }
            y1 = y + M;
            x1 = x + N;
            string a = to_string(x);
            string b = to_string(y);

            if (x1 >= imgwidth && y1 >= imgheight)
            {
                x = imgwidth - 1;
                y = imgheight - 1;
                x1 = imgwidth - 1;
                y1 = imgheight - 1;

                // crop the patches of size MxN
                Mat tiles = image_copy(Range(y, imgheight), Range(x, imgwidth));
                //save each patches into file directory
                imwrite("Resources/saved_patches/tile" + b + '_' + a + ".jpg", tiles);
                // 绘制象限 ~~~
                rectangle(img, Point(x, y), Point(x1, y1), Scalar(0, 255, 0), 1);
            }
            else if (y1 >= imgheight)
            {
                y = imgheight - 1;
                y1 = imgheight - 1;

                // crop the patches of size MxN
                Mat tiles = image_copy(Range(y, imgheight), Range(x, x + N));
                //save each patches into file directory
                imwrite("Resources/saved_patches/tile" + b + '_' + a + ".jpg", tiles);
                rectangle(img, Point(x, y), Point(x1, y1), Scalar(0, 255, 0), 1);
            }
            else if (x1 >= imgwidth)
            {
                //x = imgwidth - 1; // 这行代码错误！！
                x1 = imgwidth - 1;

                // crop the patches of size MxN
                Mat tiles = image_copy(Range(y, y + M), Range(x, imgwidth));
                //save each patches into file directory
                imwrite("Resources/saved_patches/tile" + b + '_' + a + ".jpg", tiles);
                rectangle(img, Point(x, y), Point(x1, y1), Scalar(0, 255, 0), 1);
            }
            else
            {
                // crop the patches of size MxN
                Mat tiles = image_copy(Range(y, y + M), Range(x, x + N));
                //save each patches into file directory
                imwrite("Resources/saved_patches/tile" + b + '_' + a + ".jpg", tiles);
                rectangle(img, Point(x, y), Point(x1, y1), Scalar(0, 255, 0), 1);
            }
        }
    }

    imshow("Patched Image", img);
    imwrite("Resources/patched.jpg", img);
    waitKey();

    destroyAllWindows();

	return 0;
}