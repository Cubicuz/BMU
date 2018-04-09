
#ifdef __WIN32__
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#else
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#endif // __linux__
#include "src/lab03.h"

using namespace std;
using namespace cv;

int main(){
    lab03();

}
