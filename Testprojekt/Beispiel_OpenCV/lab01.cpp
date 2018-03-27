#include "lab01.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

static void slab01(void){

	VideoCapture cap(0);

	if(!cap.isOpened()){
		cout << "Keine Kamera" << endl;
	}

	Mat img;
	Mat gray;
	for(;;){

		// acquire camera image
		cap >> img;
	
		// redo acquisition when image empty
		if (img.empty()) continue;

		// convert img -> gray
		cvtColor(img, gray, CV_BGR2GRAY);

		// white rectangle
		for (int x=15; x<50;x++){
			for(int y=100; y<200;y++){
				gray.at<unsigned char>(y, x) = 255;
			}
		}

		unsigned int value = gray.at<unsigned char>(20, 50);
		cout << value << endl;

		// display image on screen
		imshow("Webcam", gray);

		// wait 30ms for key
		if(waitKey(30) > 0) break;
	
	}


}