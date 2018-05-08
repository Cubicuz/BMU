#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#ifdef __WIN32__
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\features2d.hpp>
#else
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#endif // __linux__

#include <iostream>
#include <string>

using namespace std;
using namespace cv;

void cvtGrayToBW(Mat gray, Mat bw, uint8_t keinPlanGrenzeHalt){
    for (int x=0;x<gray.rows;x++){
        for (int y=0;y<gray.cols;y++){
            if (gray.at<uint8_t>(x, y) < keinPlanGrenzeHalt){
                bw.at<uint8_t>(x, y) = 255;
            } else {
                bw.at<uint8_t>(x, y) = 0;
            }
        }
    }

};

void cvtGrayToBW(Mat gray, Mat bw){
    cvtGrayToBW(gray, bw, 128);
};





#endif // HEADERS_H_INCLUDED
