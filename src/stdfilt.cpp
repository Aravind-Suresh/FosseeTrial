/**
 * @author {aravind}
 * Created on 2015-12-28 19:24
 *
 * C++ implementation of MATLAB function stdfilt
 *
 * References:
 * 			http://in.mathworks.com/help/images/ref/stdfilt.html
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
 * [stdfilt - Computes local standard deviation of the image]
 * @param  src   [source image (any number of channels)]
 * @param  nhood [window size for computing standard deviation, default = 3]
 * @return dst   [final image]
 */
cv::Mat stdfilt(cv::Mat src, int nhood = 3) {
  /**
   * Standard deviation is defined as sqrt(E[X^2] - (E[X])^2)
   * Here, E[X] is the expectation value or the mean value of the sequence X.
   *
   * Local standard deviation can be computed using the above formula to a local
   * window of size {nhood}. This is implemented through convolution with a mean
   * kernel.
   *
   * The mean of the squared image and the square of the mean image is computed
   * and subtracted. The result is thresholded with zero and square root is
   * taken to get the final image.
   *
   * Example:
   * 			cv::Mat dst1 = stdfilt(img);
   *
   * 			cv::Mat dst2 = stdfilt(img, 5);
   */

  cv::Mat srcC, srcSq, temp1, temp2, diff, pos, dst;

  // Defining the mean kernel of size (nhood x nhood)
  cv::Mat kernel = cv::Mat::ones( nhood, nhood, CV_32F );

  float sum = cv::sum(kernel)[0];
  float nF1 = 1.0/(sum - 1);
  float nF2 = nF1/(sum);

  // Converting CV_8U image to CV_32F image
  src.convertTo(srcC, CV_32F, 1.0/255);

  // srcSq stores src squared
  cv::pow(srcC, 2, srcSq);

  // temp1 stores mean of squared image
  cv::filter2D(srcSq, temp1, -1, nF1*kernel, cv::Point(-1, -1), 0, cv::BORDER_REFLECT);

  // Finding mean image
  cv::filter2D(srcC, temp2, -1, kernel, cv::Point(-1, -1), 0, cv::BORDER_REFLECT);

  // temp2 stores square of mean image
  cv::pow(temp2, 2, temp2);
  temp2 = temp2*nF2;

  diff = temp1 - temp2;

  // Thresholding result with zero
  pos = 0.5*(diff + cv::abs(diff));
  sqrt(pos, dst);

  // Returning dst
  return dst;
}
