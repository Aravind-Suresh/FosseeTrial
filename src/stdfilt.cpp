//
// @author {aravind}
// Created on 2015-12-28 19:24
//

// Necessary headers
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>

#include "opencv2/core/utility.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

cv::Mat stdfilt(cv::Mat src, int nhood = 3) {
  cv::Mat srcC, srcSq, temp1, temp2, diff, pos, dst;
  cv::Mat kernel = cv::Mat::ones( nhood, nhood, CV_32F );

  float sum = cv::sum(kernel)[0];
  float nF1 = 1.0/(sum - 1);
  float nF2 = nF1/(sum);
  src.convertTo(srcC, CV_32F, 1.0/255);

  cv::pow(srcC, 2, srcSq);
  cv::filter2D(srcSq, temp1, -1, nF1*kernel, cv::Point(-1, -1), 0, cv::BORDER_REFLECT);
  cv::filter2D(srcC, temp2, -1, kernel, cv::Point(-1, -1), 0, cv::BORDER_REFLECT);
  cv::pow(temp2, 2, temp2);
  temp2 = temp2*nF2;

  diff = temp1 - temp2;
  pos = 0.5*(diff + cv::abs(diff));
  sqrt(pos, dst);
  return dst;
}
