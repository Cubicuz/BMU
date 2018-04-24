#ifndef LAB06_H_INCLUDED
#define LAB06_H_INCLUDED

#include "headers.h"

using namespace std;
using namespace cv;

bool compareArea(KeyPoint a, KeyPoint b){
    return a.size > b.size;
}

void lab_06(void){
   	VideoCapture cap(0);

	if(!cap.isOpened()){
		cout << "Keine Kamera" << endl;
	}
	int key;
	double factor(1);
	Mat img;
	Mat gray, blackwhite;
	Mat screenShot;
	cap >> img;
    bool firstRun = true;
    SimpleBlobDetector::Params params;
    params.minArea = 100;
    params.maxArea = 60000;
    params.filterByArea = true;

    vector<KeyPoint> kp;


    SimpleBlobDetector blobDetector;
    blobDetector.create(params);


	// create a Window for display
	//namedWindow("Display window", WINDOW_AUTOSIZE);

	for(;;){

		// acquire camera image
		cap >> img;

		// redo acquisition when image empty
		if (img.empty()) continue;

		// convert img -> gray
		cvtColor(img, gray, CV_BGR2GRAY);



		// display image on screen
        imshow("original", gray);



		// wait 30ms for key
		key = waitKey(30);
		if (key == -1){			//do nothing

		} else if(key>=97){		//set brightness
            firstRun = false;
            screenShot = gray.clone();

        } else {				//close
			break;
		}

		// berechnung der Translationsmatrix
		if (!firstRun){
            imshow("screenshot", screenShot);
            blobDetector.detect(gray, kp);
            sort(kp.begin(), kp.end(), compareArea);
		}
	}


}


#endif // LAB06_H_INCLUDED
