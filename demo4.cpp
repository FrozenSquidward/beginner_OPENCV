// https://learnopencv.com/reading-and-writing-videos-using-opencv/
#include<opencv2/opencv.hpp>
#include<iostream>

// Namespace to nullify use of cv::function(); syntax
using namespace std;
using namespace cv;

// ��ȡ�ͱ�д��Ƶ
int demo4()
{
    // 1.initialize a video capture object
    //VideoCapture vid_capture("Resources/������.mp4");
     VideoCapture vid_capture(0);//����ͷ

    // 2.��ȡ��Ƶ֡�Ŀ�Ⱥ͸߶�
    // Obtain frame size information using get() method
    int frame_width = static_cast<int>(vid_capture.get(3));
    int frame_height = static_cast<int>(vid_capture.get(4));
    Size frame_size(frame_width, frame_height);
    cout << "frame_width" << frame_width << endl;
    cout << "frame_height" << frame_height << endl;
    int frames_per_second = 20;
    // 3.����һ����Ƶ��д������
    /*  VideoWriter(filename, apiPreference, fourcc, fps, frameSize[, isColor])
        
        filename�������Ƶ�ļ���·����
        apiPreference��API ��˱�ʶ��
        fourcc����������� 4 ���ַ����룬����ѹ��֡ ��fourcc)
        fps����������Ƶ����֡����
        frame_size����Ƶ֡�Ĵ�С
        isColor�������Ϊ�㣬��������������������ɫ֡���������������ڻҶ�֡���ñ�־Ŀǰ����Windows����֧�֣���*/
    VideoWriter output("Resources/demo4-1.mp4", VideoWriter::fourcc('M', 'J', 'P', 'G'), frames_per_second, frame_size);


    // Print error message if the stream is invalid
    if (!vid_capture.isOpened())
    {
        cout << "Error opening video stream or file" << endl;
    }
    else
    {
        // ����������� << ��һ������п��Զ��ʹ�ã�������ʵ������ʾ��endl ��������ĩ���һ�����з���
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
        // ��֡��
        int frame_count = vid_capture.get(CAP_PROP_FRAME_COUNT);
        cout << "Frame count :" << frame_count << endl;
        cout << "===================================================" << endl;
    }


    // Read the frames to the last frame
    while (vid_capture.isOpened())
    {
        // Mat��һ��ͼ���������Ƕ�ά����??
        // Initialise frame matrix
        Mat frame;

        //�÷�������һ��Ԫ�飬���е�һ��Ԫ���ǲ���ֵ����һ��Ԫ����ʵ�ʵ���Ƶ֡��
        // ����һ��Ԫ��Ϊ True ʱ������ʾ��Ƶ������Ҫ��ȡ��֡��
        // Initialize a boolean to check if frames are there or not
        bool isSuccess = vid_capture.read(frame);

        // If frames are present, show it
        if (isSuccess == true)
        {
            //display frames
            imshow("Frame", frame);
            // д������Ƶ ok
            output.write(frame);
        }

        // If frames are not there, close it
        if (isSuccess == false)
        {
            cout << "Video camera is disconnected" << endl;
            break;
        }

        // �ؼ��ֿ���֡��
        //wait 20 ms between successive frames and break the loop if key q is pressed
        int key = waitKey(20);
        if (key == 'q')
        {
            cout << "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq" << endl;
            cout << "q key is pressed by the user. Stopping the video" << endl;
            break;
        }
    }

    //�ͷ���Ƶ�������,���رմ���
    // Release the video capture object
    vid_capture.release();
    output.release();
    destroyAllWindows();
    return 0;
}