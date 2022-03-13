#include <opencv2/opencv.hpp>
#include <string>
#include <thread>
#include <sys/stat.h>
#include <unistd.h>

using namespace cv;

/*
Sets the web came to the closest native resolution

cap is video captur
width is the width of the captured image
height is the height of the captured image
*/
void setResolutionCam(VideoCapture *cap, const uint width, const uint height)
{
  cap->set(CAP_PROP_FRAME_WIDTH, width);
  cap->set(CAP_PROP_FRAME_HEIGHT, height);
}

/*
Desaturares and resizes the image.

input is the income image you wish to turn in to black and white and resize
output contains the resized and desaturated images
width is the width that output image should become
height is the height that the output image should become
*/
void imageDesatAndResize(Mat *input, Mat *output, const uint width, const uint height)
{
  if (input == NULL)
    return;

  cvtColor(*input, *output, COLOR_BGR2GRAY);
  cv::resize(*output, *output, Size(width, height), INTER_LINEAR);
}

/*
maps the value x, in a range between out_min and out_max in relation to in_min and in_max

x is the number to remap
in_min is the minimal number that x can be
in_max is the maximum number that x can be
out_min is the minimum number that the result can become
out_max is the maximum number that the result can become

returns a long that is mapped between out_min and out_max
*/
long map(int x, int in_min, int in_max, int out_min, int out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*
turnImageToAscii will look at each pixel value and find based on it's value the appropriate char from chars array.
These chars in the chars array, simulate the luminance.
Each pixel maps to a single character. So when you have 80x24 char screen the input images should be 80x24 pixels.

input is the rescaled, grey scale image to be mapped in ascii chars
*/
void turnImageToAscii(Mat *input)
{
  if (input == NULL)
    return;

  int cn = input->channels();
  static char chars[] = "Æ@#W$9876543210?!abc;:+=-,._     ";

  std::cout << "\033[1;1H\033[1;32m";
  for (int i = 0; i < input->rows; i++)
  {
    std::string s = "";
    for (int j = 0; j < input->cols; j++)
      s += chars[map(input->at<uint8_t>(i, j), 255, 0, 0, strlen(chars) - 1)];
    std::cout << s << std::endl;
  }
}

/*
just a convenience wrapper for the thread
*/
void t_resize(Mat *image, const int width, const int height)
{
  cv::resize(*image, *image, Size(width, height), INTER_LINEAR);
}

inline bool file_exists(const char *name)
{
  struct stat buffer;
  return (stat(name, &buffer) == 0);
}

bool arguments(VideoCapture *cap, int argc, char **args)
{
  if (argc == 1)
    cap->open(0);
  else if (file_exists(args[1]))
    cap->open(args[1]);
  else
    return false;

  return true;
}

int main(int argc, char **argv)
{

  Mat image, small;
  bool running = true;
  VideoCapture cap;

  if (!arguments(&cap, argc, argv))
  {
    std::cerr << "Can't open video source" << std::endl;
    exit(1);
  }

  if (!cap.isOpened())
    return 1;

	const static double delay_ms = (1/cap.get(CAP_PROP_FPS))*1000;
  // smallest native resolution this web cam has.
  setResolutionCam(&cap, 640, 480);

  std::cout << "Set your terminal to 140x51" << std::endl;
  std::cin.get();

  while (running)
  {
    cap >> image;
    if (image.empty())
      return 0;

    // turns the image into a 140, 51 pixel black and white image, that will map to 140x51 chars
    imageDesatAndResize(&image, &small, 250, 91);

    // resize the life feed to 320x240 to display, and capture keyboard events
    std::thread thread1(t_resize, &image, 320, 240);

    // takes the small black and white image and maps each pixel to a character and prints it to the terminal
    std::thread thread2(turnImageToAscii, &small);

    thread1.join();
    thread2.join();

    // show the web cam feed
    cv::imshow("RAW", image);

		if (waitKey(delay_ms) >= 0)
            break;
   //if (waitKey(41) >= 0)
   //   running = false;
  }

  return 0;
}
