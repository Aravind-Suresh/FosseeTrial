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
 #include <stdarg.h>

 #include "opencv2/core/utility.hpp"
 #include "opencv2/highgui.hpp"
 #include "opencv2/imgproc.hpp"

 int min(int n, ...) {
  int val, minVal;
  va_list vl;
  va_start(vl,n);

  minVal = va_arg(vl,int);
  for (int i=1; i<n; ++i) {
    val = va_arg(vl,int);
    minVal = (minVal < val)?minVal:val;
  }
  va_end(vl);
  return minVal;
}

 cv::Mat blurEdge(cv::Mat src, int d) {
  int h = src.rows, w = src.cols;
  cv::Mat srcPad, srcBlurRaw, srcBlur;
  cv::copyMakeBorder(src, srcPad, d, d, d, d, cv::BORDER_WRAP);
  cv::GaussianBlur(srcPad, srcBlurRaw, cv::Size(2*d+1, 2*d+1), 0);
  srcBlur = srcBlurRaw(cv::Rect(d, d, w, h));
  cv::Mat weights = cv::Mat::zeros(cv::Size(w, h), CV_32F);

  for(int i=0; i<w; ++i) {
    for(int j=0; j<h; ++j) {
      weights.at<float>(i, j) = min(j, w-j-1, i, h-i-1);
    }
  }

  weights = weights/(1.0*d);
  cv::Mat srcF, srcBlurF;
  src.convertTo(srcF, CV_32F, 1.0/255);
  srcBlur.convertTo(srcBlurF, CV_32F, 1.0/255);
  // std::cout<<src.size()<<" "<<srcBlur.size()<<" "<<weights.size();

  cv::Mat term1, term2, dst, dstF;
  cv::multiply(srcF, weights, term1);
  cv::multiply(srcBlurF, 1.0 - weights, term2);
  dstF = term1 + term2;
  dstF.convertTo(dst, CV_8UC1, 255);
  return dstF;
}

// cv::Mat constructMat(int psf, cv::Size size) {
//   cv::Mat dst = cv::Mat::zeros(size, CV_32F);
//   int rows = size.height, cols = size.width;
//
//   for(int i=0; i<rows; ++i) {
//     for(int j=0; j<cols; ++j) {
//       dst.at<float>(i, j) = psf(i, j);
//     }
//   }
//   return dst;
// }

cv::Mat deconvwnr(cv::Mat src, cv::Mat srcPsf, double nsr) {
  // Assume src is gray image
  // noise: 10**(-0.1*SNR)

  // int szX = 65, szY = 65;
  int d = 31;
  int szX = srcPsf.cols, szY = srcPsf.rows;
  double noise = std::pow(10.0, -0.1/nsr);
  int rows = src.rows, cols = src.cols;
  cv::Mat srcF, srcBlurEdge, srcPad, srcDft;
  cv::Mat matPsfDft, matPsf, matPsfPad, matPsfDftMag;
  src.convertTo(srcF, CV_32F, 1.0/255);
  srcBlurEdge = blurEdge(src, d);

  int rowsF = cv::getOptimalDFTSize(src.rows);
  int colsF = cv::getOptimalDFTSize(src.cols);

  cv::copyMakeBorder(srcBlurEdge, srcPad, 0, rowsF-rows, 0, colsF-cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
  cv::Mat planes[] = { cv::Mat_<float>(srcPad), cv::Mat::zeros(srcPad.size(), CV_32F) };
  cv::merge(planes, 2, srcDft);
  cv::dft(srcDft, srcDft, cv::DFT_COMPLEX_OUTPUT);

  //cv::Mat matPsf = cv::constructMat(psf, cv::Size(szX, szY));
  // std::cout<<srcPsf;
  srcPsf.convertTo(matPsf, CV_32F, 1.0);
  float f = 1.0/cv::sum(matPsf)[0];
  std::cout<<f<<std::endl;
  matPsf = matPsf*f;
  cv::copyMakeBorder(matPsf, matPsfPad, 0, rowsF-szY, 0, colsF-szX, cv::BORDER_CONSTANT, cv::Scalar::all(0));
  cv::Mat planesPSF[] = { cv::Mat_<float>(matPsfPad), cv::Mat::zeros(matPsfPad.size(), CV_32F) };
  cv::merge(planesPSF, 2, matPsfDft);

  cv::Mat matPsfPadF;
  std::cout<<matPsf;
  matPsfPad.convertTo(matPsfPadF, CV_32F, 1.0/255);
  cv::dft(matPsfPadF, matPsfDft, cv::DFT_COMPLEX_OUTPUT);

  cv::magnitude(planesPSF[0], planesPSF[1], matPsfDftMag);
  cv::pow(matPsfDftMag, 2, matPsfDftMag);
  cv::Mat iPsfReal, iPsfImag, iPsf, resDft, res;
  iPsfReal = planesPSF[0]/(matPsfDftMag + cv::Scalar::all(noise));
  iPsfImag = planesPSF[1]/(matPsfDftMag + cv::Scalar::all(noise));
  cv::Mat planesIPSF[] = {iPsfReal, iPsfImag};
  cv::merge(planesIPSF, 2, iPsf);

  cv::mulSpectrums(srcDft, iPsf, resDft, cv::DFT_ROWS);
  cv::idft(resDft, res, cv::DFT_REAL_OUTPUT + cv::DFT_SCALE);
  //std::cout<<res;
  std::cout<<res.size()<<std::endl;
  //cv::imshow("res", res);
  return res;
}
