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


#endif // HEADERS_H_INCLUDED
