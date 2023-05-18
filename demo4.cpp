// https://learnopencv.com/reading-and-writing-videos-using-opencv/
#include<opencv2/opencv.hpp>
#include<iostream>

// Namespace to nullify use of cv::function(); syntax
using namespace std;
using namespace cv;

// 读取和编写视频
int demo4()
{
    // 1.initialize a video capture object
    //VideoCapture vid_capture("Resources/整薯条.mp4");
     VideoCapture vid_capture(0);//摄像头

    // 2.获取视频帧的宽度和高度
    // Obtain frame size information using get() method
    int frame_width = static_cast<int>(vid_capture.get(3));
    int frame_height = static_cast<int>(vid_capture.get(4));
    Size frame_size(frame_width, frame_height);
    cout << "frame_width" << frame_width << endl;
    cout << "frame_height" << frame_height << endl;
    int frames_per_second = 20;
    // 3.创建一个视频编写器对象
    /*  VideoWriter(filename, apiPreference, fourcc, fps, frameSize[, isColor])
        
        filename：输出视频文件的路径名
        apiPreference：API 后端标识符
        fourcc：编解码器的 4 个字符代码，用于压缩帧 （fourcc)
        fps：创建的视频流的帧速率
        frame_size：视频帧的大小
        isColor：如果不为零，编码器将期望并编码颜色帧。否则，它将适用于灰度帧（该标志目前仅在Windows上受支持）。*/
    VideoWriter output("Resources/demo4-1.mp4", VideoWriter::fourcc('M', 'J', 'P', 'G'), frames_per_second, frame_size);


    // Print error message if the stream is invalid
    if (!vid_capture.isOpened())
    {
        cout << "Error opening video stream or file" << endl;
    }
    else
    {
        // 流插入运算符 << 在一个语句中可以多次使用，如上面实例中所示，endl 用于在行末添加一个换行符。
        /*char str[] = "Hello C++";
        cout << "Value of str is : " << str << endl;*/
        cout << "===================================================" << endl;

        // Obtain fps and frame count by get() method and print
        // You can replace 5 with CAP_PROP_FPS as well, they are enumerations
        // FPS
        int fps = vid_capture.get(CAP_PROP_FPS);
        cout << "Frames per second :" << fps << endl;

        // Obtain frame_count using opencv built in frame count reading method
        // You can replace 7 with CAP_PROP_FRAME_COUNT as well, they are enumerations
        // 总帧数
        int frame_count = vid_capture.get(CAP_PROP_FRAME_COUNT);
        cout << "Frame count :" << frame_count << endl;
        cout << "===================================================" << endl;
    }


    // Read the frames to the last frame
    while (vid_capture.isOpened())
    {
        // Mat是一种图像容器，是二维向量??
        // Initialise frame matrix
        Mat frame;

        //该方法返回一个元组，其中第一个元素是布尔值，下一个元素是实际的视频帧。
        // 当第一个元素为 True 时，它表示视频流包含要读取的帧。
        // Initialize a boolean to check if frames are there or not
        bool isSuccess = vid_capture.read(frame);

        // If frames are present, show it
        if (isSuccess == true)
        {
            //display frames
            imshow("Frame", frame);
            // 写入新视频 ok
            output.write(frame);
        }

        // If frames are not there, close it
        if (isSuccess == false)
        {
            cout << "Video camera is disconnected" << endl;
            break;
        }

        // 关键字控制帧数
        //wait 20 ms between successive frames and break the loop if key q is pressed
        int key = waitKey(20);
        if (key == 'q')
        {
            cout << "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq" << endl;
            cout << "q key is pressed by the user. Stopping the video" << endl;
            break;
        }
    }

    //释放视频捕获对象,并关闭窗口
    // Release the video capture object
    vid_capture.release();
    output.release();
    destroyAllWindows();
    return 0;
}