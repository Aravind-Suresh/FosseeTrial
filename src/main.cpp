// Necessary headers
#include <math.h>
#include <stdlib.h>
#include <string>

#include "opencv2/core/utility.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

int main(int argc, char **argv) {
  cv::Mat img = cv::imread(argv[1]);
  cv::Mat dst;
  dst = stdfilt(img);

  cv::imshow("src", img);
  cv::imshow("img", dst);
  cv::waitKey(0);
}
