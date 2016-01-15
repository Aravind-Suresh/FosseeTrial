/**
 * @author {aravind}
 * Created on 2016-01-16 02:17
 *
 * Test program for my implementations
 */

// Necessary headers
#include <math.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "opencv2/core/utility.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "util.h"

int main(int argc, char **argv) {
  if(argc != 2) {
    std::cout<<"Usage : "<<argv[0]<<" <source image>"<<std::endl;
    exit(-1);
  }

  cv::Mat img = cv::imread(argv[1], 0);
  cv:: threshold(img, img, 127, 255, cv::THRESH_BINARY);
  // std::cout<<img;
  cv::Mat dst = bwpack(img), out;
  cv::normalize(dst, out, 0, 255, cv::NORM_MINMAX, CV_8UC1);

  // std::cout<<out;

  cv::imshow("Input image", img);
  cv::imshow("Output image", out);
  cv::waitKey(0);

  return 0;
}
