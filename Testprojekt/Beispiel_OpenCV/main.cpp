#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include "lab01.h"
#include "lab02.h"


using namespace std;
using namespace cv;

int main(){
	VideoCapture cap(0);

	if(!cap.isOpened()){
		cout << "Keine Kamera" << endl;
	}
	int key;
	long val;
	double factor(1);
	Mat img;
	Mat gray;
	cap >> img;
	Mat brightnessMat, contrastMat, sobelGxMat, sobelGyMat, sobelGMat;
	brightnessMat = Mat(img.rows, img.cols, CV_8UC1);
	contrastMat = Mat(img.rows, img.cols, CV_8UC1);
	sobelGxMat = Mat(img.rows, img.cols, CV_8UC1);
	sobelGyMat = Mat(img.rows, img.cols, CV_8UC1);
	sobelGMat = Mat(img.rows, img.cols, CV_8UC1);



	// create a Window for display
	namedWindow("Display window", WINDOW_AUTOSIZE);
		
	for(;;){
		
		// acquire camera image
		cap >> img;
		
		// redo acquisition when image empty
		if (img.empty()) continue;

		// convert img -> gray
		cvtColor(img, gray, CV_BGR2GRAY);


		for(int x=0;x<gray.rows;x++){

			for(int y=0;y<gray.cols;y++){
				// apply brightness
				val = gray.at<unsigned char>(x, y);
				val *= factor;
				if (val > 255)
					val=255;
				brightnessMat.at<unsigned char>(x, y) = val;

				// apply contrast
				val = gray.at<unsigned char>(x, y);
				if (val<128){
					val /= factor;
				} else {
					val *= factor;
				}
				if (val < 0)
					val=0;
				if (val>255)
					val=255;
				contrastMat.at<unsigned char>(x, y) = val;

				// apply sobel
				// gx
				if (y>0 && x>0){

				}



				sobelGxMat.at<unsigned char>(x, y) = val;
			}
		}

		// apply contrast
	
		
		// display image on screen
		imshow("Display window", contrastMat);

		// wait 30ms for key
		//if(waitKey(30) > 0) break;


		// wait 30ms for key
		key = waitKey(30);
		if (key == -1){			//do nothing

		} else if(key>=97){		//set brightness
			factor = 1 + ((double)key - 97)/10;
			cout << factor << endl;
		} else {				//close
			break;	
		}
	}


}