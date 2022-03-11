#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;

void setResolutionCam(VideoCapture *cap, const uint width, const uint height){
    cap->set(CAP_PROP_FRAME_WIDTH, width);
    cap->set(CAP_PROP_FRAME_HEIGHT, height);
}

int main()
{
    
    Mat image;
    VideoCapture cap(0);
    if (!cap.isOpened())
    {
        return 1;
    }

    setResolutionCam(&cap, 640, 480);

    while (1)
    {
        cap >> image;
        cv::imshow("RAW", image);
        waitKey(25);
    }
    
    return 0;
}