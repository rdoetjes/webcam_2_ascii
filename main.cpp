#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;

void setResolutionCam(VideoCapture *cap, const uint width, const uint height)
{
    cap->set(CAP_PROP_FRAME_WIDTH, width);
    cap->set(CAP_PROP_FRAME_HEIGHT, height);
}

void processImage(Mat *input, Mat *output)
{
    cvtColor(*input, *output, COLOR_BGR2GRAY);
    cv::resize(*output, *output, Size(160, 48), INTER_LINEAR);
}

long map(int x, int in_min, int in_max, int out_min, int out_max) {
   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void turnToAscii(Mat *input)
{
    int cn = input->channels();
    static char chars[] = "Æ@#W$9876543210?!abc;:+=-,._         ";
    for (int i = 0; i < input->rows; i++)
    {
        std::string s = "";
        for (int j = 0; j < input->cols; j++)
        {
            s += chars[map(input->at<uint8_t>(i,j), 255, 0, 0 ,strlen(chars)-1)];
        }
        std::cout << s << std::endl;
    }
}

int main()
{

    Mat image, small;
    bool running = true;

    VideoCapture cap(0);
    if (!cap.isOpened())
        return 1;

    setResolutionCam(&cap, 640, 480);

    while (running)
    {
        cap >> image;
        processImage(&image, &small);
        cv::imshow("RAW", image);
        cv::imshow("SMALL", small);
        turnToAscii(&small);
        if (waitKey(30) >= 0)
            running = false;
    }

    return 0;
}