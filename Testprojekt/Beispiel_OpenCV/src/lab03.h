#ifndef LAB03_H_INCLUDED
#define LAB03_H_INCLUDED

#ifdef __WIN32__
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#else
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#endif // __linux__

#include <iostream>
#include <string>

using namespace std;
using namespace cv;

void lab03(){
    	VideoCapture cap(0);

	if(!cap.isOpened()){
		cout << "Keine Kamera" << endl;
	}
	int key;
	double factor(1);
	Mat img;
	Mat gray;
	cap >> img;
	int width, height, grayDepth, mostGrayIndex, mostGrayValue;
	height = img.rows;
	grayDepth = 256;
	width = img.cols;
	Mat histoMat = Mat(height, width, CV_8UC3);
    int* histogram = new int [grayDepth];


	// create a Window for display
	//namedWindow("Display window", WINDOW_AUTOSIZE);

	for(;;){

		// acquire camera image
		cap >> img;

		// redo acquisition when image empty
		if (img.empty()) continue;

		// convert img -> gray
		cvtColor(img, gray, CV_BGR2GRAY);

        // zero the variables
        for (int i=0;i<grayDepth;i++){
            histogram[i]=0;
        }
        mostGrayValue = mostGrayIndex = 0;
        histoMat.setTo(Scalar(0, 0, 0));

        // generate histogram
		for(int x=0;x<gray.rows;x++){

			for(int y=0;y<gray.cols;y++){
                histogram[gray.at<uint8_t>(x, y)]++;
			}
        }

        // search the most occuring gray for scaling
        for (int i=0;i<grayDepth;i++){
            if (histogram[i] > mostGrayValue){
                mostGrayValue = histogram[i];
                mostGrayIndex = i;
            }
        }

        // draw histogramm
        for (int i=0;i<grayDepth;i++){
            Rect myRectangle(2*i, 0, 2, (histogram[i] * (height-2) / mostGrayValue));
            rectangle(histoMat, myRectangle, Scalar(0, 255, 0));
        }

        cv::putText(histoMat, std::to_string(mostGrayValue), CvPoint(2*grayDepth + 5, 20), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0));
        //cout << "print matrixes" << endl;
		// display image on screen
        imshow("original", gray);
        imshow("histogram", histoMat);
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
};

#endif // LAB03_H_INCLUDED
