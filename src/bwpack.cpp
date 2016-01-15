/**
 * @author {aravind}
 * Created on 2016-01-16 01:26
 *
 * C++ implementation of MATLAB function bwpack
 *
 * References:
 * 			http://in.mathworks.com/help/images/ref/bwpack.html
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

 int bit32Int(int* binArr, int size) {
   int val = 0, cur = 1;
   for(i=0; i<size; ++i) {
     val += binArr[i]*cur;
     cur = cur << 1;
   }
   return val;
 }

 cv::Mat bwpack(cv::Mat src) {
  int rows = src.rows, cols = src.cols;

  // According to MATLAB definition
  int SIZE_INT = 32, idx = 0;
  int rowsF = int(ceil(1.0*rows/SIZE_INT));
  cv::Size size(rowsF, cols);

  cv::Mat srcPad;
  int d = rowsF*SIZE_INT - rows;
  cv::copyMakeBorder(src, srcPad, 0, 0, 0, d, cv::BORDER_CONSTANT, 0);

  // Transposing srcPad so as to traverse it columnwise
  cv::Mat srcPadT = srcPad.t();

  // CV_32S1 - 32 bit signed integer, 1 channel
  cv::Mat dst = cv::Mat::zeros(size, CV_32S1);

  for(int i=0; i<cols; ++i) {
    for(int j=0; j<rowsF; ++j) {
      const int* ptr = srcPadT.ptr<int>(j*SIZE_INT);
      dst.at<int>(j, i) = bit32Int(ptr, SIZE_INT);
    }
  }

  // Returning bwpacked mat
  return dst;
}
