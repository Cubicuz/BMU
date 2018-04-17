
#ifdef __WIN32__
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "src\lab02.h"
#include "src\lab03.h"
#else
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "src/lab02.h"
#include "src/lab03.h"
//#include "src/lab04.h"
#include "src/lab05.h"
#endif // __linux__

using namespace std;
using namespace cv;

int main(){
    lab02();

}
