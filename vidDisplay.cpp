//Jose Joseph Thandapral
//CS5330
//Project 1 : Real-time filtering
// The following is the declaration of the function prototypes and main()
//that implements the real-time filtering project

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include<opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
int greyscale(cv::Mat& src, cv::Mat& dst);
int blur5x5(cv::Mat& src, cv::Mat& dst);
int sobelX3x3(cv::Mat& src, cv::Mat& dst);
int sobelY3x3(cv::Mat& src, cv::Mat& dst);
int magnitude(cv::Mat& sx, cv::Mat& sy, cv::Mat& dst);
int blurQuantize(cv::Mat& src, cv::Mat& dst, int levels);
int cartoon(cv::Mat& src, cv::Mat& dst, int levels, int magThreshold);
int negative(cv::Mat& src, cv::Mat& dst);

int main(int argc, char* argv[]) {
    cv::VideoCapture* capdev;
    cv::Mat grayImage;
    cv::Mat grayImagefunc;
    cv::Mat blurImage;
    cv::Mat sobelXImage;
    cv::Mat sobelYImage;
    cv::Mat magImage;
    cv::Mat blurQuantImage;
    cv::Mat sobelXdisplaysrc;
    cv::Mat sobelYdisplaysrc;
    cv::Mat gradsrc;
    cv::Mat negImage;
    cv::Mat cartoonImage;
    char key1;

    // open the video device
    capdev = new cv::VideoCapture(1);
    if (!capdev->isOpened()) {
        printf("Unable to open video device\n");
        return(-1);
    }

    // get some properties of the image
    cv::Size refS((int)capdev->get(cv::CAP_PROP_FRAME_WIDTH),
        (int)capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
    printf("Expected size: %d %d\n", refS.width, refS.height);

    cv::namedWindow("Video", 1); // identifies a window
    cv::Mat frame;

    for (;;) {
        *capdev >> frame; // get a new frame from the camera, treat as a stream
        if (frame.empty()) {
            printf("frame is empty\n");
            break;
        }

        // see if there is a waiting keystroke
        char key = cv::waitKey(10);
        if (key == '0' || key == -1)
        {
            cv::imshow("Video", frame);
        }
        else if (key != -1)
        {
            key1 = key;
        }
        else if (key == 's')
        {
            if (cv::imwrite("savedImage.jpg", frame))
            {
                printf("Successfully saved savedImage.jpg to current directory");
            }
        }
        if (key == 'q') {
            break;
        }
        else if (key1 == 'h')
        {
            cv::cvtColor(frame, grayImage, cv::COLOR_BGR2GRAY);
            cv::imshow("Video", grayImage);
        }
        else if (key1 == 'g')
        {
            grayImagefunc.create(frame.size(), frame.type());
            greyscale(frame, grayImagefunc);
            cv::imshow("Video", grayImagefunc);
        }
        else if (key1 == 'b')
        {
            blurImage.create(frame.size(), frame.type());
            blur5x5(frame, blurImage);
            cv::imshow("Video", blurImage);
        }
        else if (key1 == 'x')
        {
            sobelX3x3(frame, gradsrc);
            cv::convertScaleAbs(gradsrc, sobelXdisplaysrc);
            cv::imshow("Video", sobelXdisplaysrc);
        }
        else if (key1 == 'y')
        {
            sobelY3x3(frame, gradsrc);
            cv::convertScaleAbs(gradsrc, sobelYdisplaysrc);
            cv::imshow("Video", sobelYdisplaysrc);
        }
        else if (key1 == 'l')
        {
            blurQuantImage.create(frame.size(), frame.type());
            blurQuantize(frame, blurQuantImage, 15);
            cv::imshow("Video", blurQuantImage);
        }
        else if (key1 == 'm')
        {
            sobelX3x3(frame, gradsrc);
            cv::convertScaleAbs(gradsrc, sobelXdisplaysrc);
            sobelY3x3(frame, gradsrc);
            cv::convertScaleAbs(gradsrc, sobelYdisplaysrc);
            magImage.create(frame.size(), frame.type());
            magnitude(sobelXdisplaysrc, sobelYdisplaysrc, magImage);
            cv::imshow("Video", magImage);
        }
        else if (key1 == 'c')
        {
            cartoon(frame, cartoonImage, 15, 20);
            cv::imshow("Video", cartoonImage);
        }
        else if (key1 == 'n') // task 10: displaying the negative of an image
        {
            negImage.create(frame.size(), frame.type());
            negative(frame, negImage);
            cv::imshow("Video", negImage);
        }

    }


    delete capdev;
    return(0);
}