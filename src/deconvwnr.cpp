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

cv::Mat constructMat(psf, cv::Size size) {
  cv::Mat dst = cv::Mat::zeros(size, CV_32F);
  int rows = size.height, cols = size.width;

  for(int i=0; i<rows; ++i) {
    for(int j=0; j<cols; ++j) {
      dst.at<float>(i, j) = psf(i, j);
    }
  }
  return dst;
}

cv::deconvwnr(cv::Mat src, ) {
  // Assume src is gray image
  // noise: 10**(-0.1*SNR)

  int rows = src.rows, cols = src.cols;
  cv::Mat srcF, srcBlurEdge, srcPad, srcDft;
  src.convertTo(srcF, CV_32F, 1.0/255);
  srcBlurEdge = blurEdge(src, d);

  int rowsF = cv::getOptimalDFTSize(src.rows);
  int colsF = cv::getOptimalDFTSize(src.cols);

  cv::copyMakeBorder(srcBlurEdge, srcPad, 0, rowsF-rows, 0, colsF-cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
  cv::Mat planes[] = { cv::Mat_<float>(srcPad), cv::Mat::zeros(srcPad.size(), CV_32F) };
  cv::merge(planes, 2, srcDft);
  cv::dft(srcDft, srcDft);

  cv::Mat matPsf = cv::constructMat(psf, src.size());
  matPsf = matPsf/cv::sum(matPsf);
  cv::copyMakeBorder(matPsf, matPsfPad, 0, rowsF-rows, 0, colsF-cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

}
