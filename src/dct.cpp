/**
 * @author {aravind}
 * Created on 2016-02-07 23:19
 *
 * C++ implementation of MATLAB function dct
 *
 * References:
 * 			http://in.mathworks.com/help/images/ref/dct.html
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

/**
 * [dct Computes the Discrete Cosine Transform of the array]
 * @param  src [Input array, can be an image or a sequence]
 * @param  n   [Optional integer to pad at the end of the sequence/image]
 * @return dst [discrete cosine tranformed image]
 */
cv::Mat dct(cv::Mat src, int n = 0) {
  /**
   * dct performs the Discrete Cosin Transform on the input image
   * or sequence whichever is provided.
   * The optional parameter n if given, pads the image by length n,
   * before computing the transform.
   *
   * Example:
   * 			// Computes dct on img
   * 			cv::Mat dst = dct(img);
   *
   * 			// Pads img by 30 pixels and then computes the transform
   * 			cv::Mat dst = dct(img, 30);
   */

  // Assertion
  assert(!src.empty());
  cv::Mat srcC = src.clone(), dst;

  if(src.type() == CV_8UC1) {
    // Converting src to float before computing dct
    src.convertTo(srcC, CV_32FC1);
  }

  // Padding image with n pixels if necessary
  if(n) cv::copyMakeBorder(srcC, srcC, 0, 0, 0, n, cv::BORDER_CONSTANT, 0);

  // Computing the transform
  cv::dct(srcC, dst);

  // Returning dst
  return dst;
}
