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

 /**
  * [bit32Int Function to return integer given array of bits - 0,1]
  * @param  binArr [input array]
  * @param  size   [size of array]
  * @return val    [value of the integer]
  */
 int bit32Int(int* binArr, int size) {
   int val = 0, cur = 1;
   for(i=0; i<size; ++i) {
     // Incrementing val with place value of the bit if its 1
     if(binArr[i]) val += cur;
     cur = cur << 1;
   }
   // Returning val
   return val;
 }

 /**
  * [bwpack Constructs a packed image of 32-bit integers from a thresholded image]
  * @param  src [input binary image]
  * @return dst [packed image]
  */
 cv::Mat bwpack(cv::Mat src) {
   /**
    * bwpack packs the uchar binary image src into the int array dst,
    * which is known as a packed binary image.
    * Because each 8-bit pixel value in the binary image has only two possible values,
    * 1 and 0, bwpack can map each pixel to a single bit in the packed output image.
    *
    * It processes the image pixels by column,
    * mapping groups of 32 pixels into the bits of a int value.
    * The first pixel in the first row corresponds to the least significant bit
    * of the first int element of the output array.
    * The first pixel in the 32nd input row corresponds to the most significant bit of this same element.
    *
    * Example:
    * 			cv::Mat dst = bwpack(src);
    */
  int rows = src.rows, cols = src.cols;

  // According to MATLAB definition
  int SIZE_INT = 32, idx = 0;
  int rowsF = int(ceil(1.0*rows/SIZE_INT));
  cv::Size size(rowsF, cols);

  // Padding src image so as to account for higher bits
  cv::Mat srcPad;
  int d = rowsF*SIZE_INT - rows;
  cv::copyMakeBorder(src, srcPad, 0, 0, 0, d, cv::BORDER_CONSTANT, 0);

  // Transposing srcPad so as to traverse it columnwise
  cv::Mat srcPadT = srcPad.t();

  // CV_32S1 - 32 bit signed integer, 1 channel
  cv::Mat dst = cv::Mat::zeros(size, CV_32S1);

  for(int i=0; i<cols; ++i) {
    for(int j=0; j<rowsF; ++j) {
      // Constructing a ptr and traversing
      const int* ptr = srcPadT.ptr<int>(j*SIZE_INT);
      dst.at<int>(j, i) = bit32Int(ptr, SIZE_INT);
    }
  }

  // Returning bwpacked mat
  return dst;
}
