#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;

void setResolutionCam(VideoCapture *cap, const uint width, const uint height)
{
    cap->set(CAP_PROP_FRAME_WIDTH, width);
    cap->set(CAP_PROP_FRAME_HEIGHT, height);
}

int main()
{

    Mat image, small;
    bool running = true;

    VideoCapture cap(0);
    if (!cap.isOpened())
        return 1;

    setResolutionCam(&cap, 80, 24);

    while (running)
    {
        cap >> image;   
        cv::imshow("RAW", image);
        cvtColor(image, small, COLOR_BGR2GRAY);
        cv::resize(small, small, Size(80, 24), INTER_LINEAR);
        cv::imshow("SMALL", small);

        if  (waitKey(30) >=0 ) running = false;
    }

    return 0;
}