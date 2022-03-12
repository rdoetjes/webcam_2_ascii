#include <opencv2/opencv.hpp>
#include <string>
#include <thread>

using namespace cv;

void setResolutionCam(VideoCapture *cap, const uint width, const uint height)
{
    cap->set(CAP_PROP_FRAME_WIDTH, width);
    cap->set(CAP_PROP_FRAME_HEIGHT, height);
}

void imageDesatAndResize(Mat *input, Mat *output, const int width, const int height)
{
    cvtColor(*input, *output, COLOR_BGR2GRAY);
    cv::resize(*output, *output, Size(width, height), INTER_LINEAR);
}

long map(int x, int in_min, int in_max, int out_min, int out_max) {
   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void turnImageToAscii(Mat *input)
{
    int cn = input->channels();
    static char chars[] = "Æ@#W$9876543210?!abc;:+=-,._         ";

    std::cout << "\033[1;1H";
    for (int i = 0; i < input->rows; i++)
    {
        std::string s = "";
        for (int j = 0; j < input->cols; j++)
        {
            s += "\033[1;32m";
            s += chars[map(input->at<uint8_t>(i,j), 255, 0, 0 ,strlen(chars)-1)];
        }
        std::cout << s << std::endl;
    }
}

void t_resize(Mat *image){
    cv::resize(*image, *image, Size(320, 240), INTER_LINEAR);
}

int main()
{

    Mat image, small;
    bool running = true;

    VideoCapture cap(0);
    if (!cap.isOpened())
        return 1;

    setResolutionCam(&cap, 640, 480);
    std::cout << "Set your terminal to 140x51" << std::endl;
    std::cin.get();

    while (running)
    {
        cap >> image;
        imageDesatAndResize(&image, &small, 140, 51);
        
        std::thread thread1(t_resize, &image);
        std::thread thread2(turnImageToAscii, &small);
        thread1.join();
        thread2.join();

        cv::imshow("RAW", image);
        if (waitKey(20) >= 0)
            running = false;
    }

    return 0;
}