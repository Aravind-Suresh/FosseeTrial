/**
 * @author {aravind}
 * Created on 2016-01-04 11:55
 *
 * Utility header file
 */

#ifndef UTIL_H
#define UTIL_H

// Necessary headers
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "opencv2/core/utility.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

// Source: src/imquantize.cpp
std::vector<int> linspace(int start, int end, int n);
cv::Mat imquantize(cv::Mat src, std::vector<int> thresh);
cv::Mat imquantize(cv::Mat src, int thresh);

// Source: src/stdfilt.cpp
cv::Mat stdfilt(cv::Mat src, int nhood = 3);

#endif
