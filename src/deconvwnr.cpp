/**
 * @author {aravind}
 * Created on 2016-01-13 20:03
 *
 * C++ implementation of MATLAB function deconvwnr
 *
 * References:
 * 			http://in.mathworks.com/help/images/ref/deconvwnr.html
 */

 // Necessary headers
 #include <iostream>
 #include <math.h>
 #include <stdlib.h>
 #include <string>
 #include <vector>

 #include "opencv2/core/utility.hpp"
 #include "opencv2/highgui.hpp"
 #include "opencv2/imgproc.hpp"

cv::Mat blurEdge(cv::Mat src, int d) {
  int h = src.rows, w = src.cols;
  cv::Mat srcPad, srcBlur;
  cv::copyMakeBorder(src, srcPad, d, d, d, d, cv::BORDER_WRAP);
  cv::GaussianBlur(srcPad, srcBlur, cv::Size(2*d+1, 2*d+1));

  cv::Mat weights = cv::Mat::zeros(cv::Size(h, w), CV_32F);

  for(int i=0; i<h; ++i) {
    for(int j=0; j<w; ++j) {
      weights.at<float>(i, j) = min(j, w-j-1, i, h-i-1);
    }
  }

  weights = weights/(1.0*d);
  return src*weights + srcBlur*(1.0 - weights);
}

cv::Mat motionKernel(float angle, int d, int sz) {
  cv::Mat kern = cv::Mat::ones((1, d), CV_32F);
  float cosA = cos(angle), sinA = sin(angle);
  int sz2 = sz/2;

}

cv::Mat defocusKernel(int d, int sz) {
  cv::Mat kern = cv::Mat::zeros(cv::Size(sz, sz), CV_8UC1);
  cv::circle(kern, cv::Size(sz, sz), d, 255, -1, cv::LINE_AA, 1);
  kern.convertTo(srcC, CV_32F, 1.0/255);
  return kern;
}

cv::deconvwnr(cv::Mat src) {
  assert()
}
