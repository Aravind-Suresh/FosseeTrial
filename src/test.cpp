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

cv::Mat defocusKernel(int d, int sz) {
   cv::Mat kern = cv::Mat::zeros(cv::Size(sz, sz), CV_8UC1);
   cv::circle(kern, cv::Size(sz, sz), d, 255, -1, cv::LINE_AA, 1);
   //kern.convertTo(srcC, CV_32F, 1.0/255);
   cv::imshow("kern", kern);
   return kern;
 }

int main(int argc, char **argv) {
  if(argc != 2) {
    std::cout<<"Usage : "<<argv[0]<<" <source image>"<<std::endl;
    exit(-1);
  }

  cv::Mat img = cv::imread(argv[1], 0);
  std::cout<<img.size();
  // cv:: threshold(img, img, 127, 255, cv::THRESH_BINARY);
  //cv::Mat psf = defocusKernel(22, 65);
  //cv::Mat::ones(cv::Size(5, 5), CV_8UC1);//(cv::Mat_<int>(3, 3) << 1,1,1, 1,1,1, 1,1,1);

  //cv::Mat dst = deconvwnr(img, psf, 0.04), out;
  //cv::normalize(dst, out, 0, 255, cv::NORM_MINMAX, CV_8UC1);

  //std::cout<<out;

  cv::Mat out;
  out = dct(img, 200);

  cv::imshow("Input image", img);
  cv::imshow("Output image", out);
  cv::waitKey(0);

  return 0;
}
