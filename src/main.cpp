//
// @author {aravind}
// Created on 2016-01-03 02:30
//

// Necessary headers
#include <math.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "opencv2/core/utility.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

int main(int argc, char **argv) {
  cv::Mat img = cv::imread(argv[1], 0);
  cv::Mat dst;
  std::vector<int> thresh = linspace(0, 255, 3);

  // dst = stdfilt(img);
  dst = imquantize(img, thresh);
  // dst = imquantize(img, 100);
  cv::normalize(dst, dst, 0, 255, cv::NORM_MINMAX, -1);

  cv::imshow("src", img);
  cv::imshow("img", dst);
  cv::waitKey(0);
}
