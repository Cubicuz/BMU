#include "lab02.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

static void slab02(void){
	VideoCapture cap(0);

	if(!cap.isOpened()){
		cout << "Keine Kamera" << endl;
	}
	int key;
	int val;
	double brightness(1);
	Mat img;
	Mat gray;
	cap >> img;
	Mat result;
	result = Mat(img.rows, img.cols, CV_8UC1, 0);
	for(;;){
		
		// acquire camera image
		cap >> img;
		
		// redo acquisition when image empty
		if (img.empty()) continue;

		// convert img -> gray
		cvtColor(img, gray, CV_BGR2GRAY);

		// apply brightness
		for(int x=0;x<gray.rows;x++){
			for(int y=0;y<gray.cols;y++){
				val = gray.at<char>(x, y);
				val *= brightness;
				if (val > 255)
					val=255;
				result.at<char>(x, y) = val;
			}
		}

		
		// display image on screen
		imshow("Webcam", result);

		// wait 30ms for key
		key = waitKey(30);
		if (key == -1){			//do nothing

		} else if(key>97){		//set brightness
			brightness = key - 96;

		} else {				//close
			break;	
		}
	}


}