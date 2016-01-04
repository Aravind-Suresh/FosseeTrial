/**
 * @author {aravind}
 * Created on 2016-01-03 02:31
 *
 * C++ implementation of MATLAB function imquantize
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
 * [linspace - Constructs linearly spaced vector of length n between start and end values ( both inclusive )]
 * @param  start   [start value]
 * @param  end     [end value]
 * @param  n       [length of the vector]
 * @return vec     [linearly spaced vector]
 */
std::vector<int> linspace(int start, int end, int n) {
  /**
   * A utility function for generating a vector of linearly spaced integers.
   *
   * NOTE: For demo purpose
   */

  // Finding diff
  float diff = (end - start)*1.0/(n);
  std::vector<int> vec(n);
  float val = start;

  for(int i=0; i<n; ++i) {
    vec[i] = val;
    // Adding diff to val
    val += diff;
  }

  // Returning the vector
  return vec;
}

/**
 * [imquantize - Quantizes image between using specified quantization values contained in the vector thresh]
 * @param  src    [source image]
 * @param  thresh [vector containing the quantization values]
 * @return dst    [final labelled image]
 */
cv::Mat imquantize(cv::Mat src, std::vector<int> thresh) {
  /**
   * If thresh contains N integers for quantization,
   * labelling source image is based on the following relation,
   *
   * If src(x, y) <= levels(1), then dst(x, y) = 1.
   * If levels(m-1) < src(x, y)  <=  levels(m) , then dst(x, y) = m.
   * If src(x, y) > levels(N), then dst(x, y) = N + 1.
   *
   * Example:
   * 			std::vector<int> thresh = linspace(0, 255, 3);
   * 			dst = imquantize(img, thresh);
   *
   * 			dst = imquantize(img, 100);
   */

  // Defining dst
  cv::Mat dst(src.size(), CV_8UC1, cv::Scalar::all(1));

  // Defining an iterator to iterate through thresh
  std::vector<int>::iterator begin = thresh.begin(), end = thresh.end();

  for(std::vector<int>::iterator it = begin; it != end; ++it) {
    // temp composed of 0 (where src(x, y) < *it) and 1 ( where src(x, y) > *it)
    cv::Mat temp = (src > *it)/255;

    // Adding temp to dst, when this is done for all values, the image gets labelled
    dst += temp;
  }

  // Returning dst
  return dst;
}

/**
 * [imquantize - Overloaded version of above function,
 * which takes a single integer as threshold and quantizes image to 2 levels]
 * @param  src    [source image]
 * @param  thresh [threshold (integer)]
 * @return dst    [final labelled image]
 */
cv::Mat imquantize(cv::Mat src, int thresh) {
  // Defining vector of length 1, containing thresh
  std::vector<int> vecThresh(1, thresh);
  return imquantize(src, vecThresh);
}
