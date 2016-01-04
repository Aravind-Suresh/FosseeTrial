/**
 * @author {aravind}
 * Created on 2016-01-03 02:30
 *
 * Sample demo program for my implementations
 */

// Necessary headers
#include <math.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "opencv2/core/utility.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "util.h"

int main(int argc, char **argv) {
  /**
   * Trial:
   * 			// FOR STDFILT DEMO
   * 			./bin/demo images/test1.jpg 0
   *
   * 			// FOR IMQUANTIZE DEMO
   * 			./bin/demo images/test1.jpg 1
   */
  if(argc != 3) {
    std::cout<<"Usage : "<<argv[0]<<" <source image> <mode>"<<std::endl;
    std::cout<<"<mode> : 0 for stdfilt demo, 1 for imquantize demo"<<std::endl;
    exit(-1);
  }

  cv::Mat img = cv::imread(argv[1], 0);
  cv::Mat dst;

  int mode = atoi(argv[2]);

  if(mode) {
      dst = stdfilt(img);
  }
  else {
    // Constructing linearly spaced vector thresh
    std::vector<int> thresh = linspace(0, 255, 3);
    dst = imquantize(img, thresh);
    // dst = imquantize(img, 100);

    // Normalizing image for display purpose
    cv::normalize(dst, dst, 0, 255, cv::NORM_MINMAX, -1);
  }

  cv::imshow("Input image", img);
  cv::imshow("Output image", dst);
  cv::waitKey(0);
}
