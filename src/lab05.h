#ifndef LAB05_INCLUDED
#define LAB05_INCLUDED

#include "headers.h"

uint8_t interpolation(Mat* source, float x, float y){
    int64_t x1 =(int64_t) x;
    int64_t y1 =(int64_t) y;
    int64_t x2 = x1+1;
    int64_t y2 = y1+1;
    float dist1 = (x2-x);
    float dist2 = (x-x1);
    float interpol1 = dist1 * source->at<uint8_t>(x1, y1) + dist2 * source->at<uint8_t>(x2, y1);
    float interpol2 = dist1 * source->at<uint8_t>(x1, y2) + dist2 * source->at<uint8_t>(x2, y2);
    return (uint8_t) ((y2-y)*interpol1 + (y-y1)*interpol2);
};



int translationScaling(Mat* source, Mat* target, int64_t xOffset, int64_t yOffset, float scalingFactor){
    float xSource, ySource;
    for (int64_t x=0; x < target->rows;x++){
        xSource = (x + xOffset)*scalingFactor;
        if (xSource < 0 || xSource >= source->rows){
            for(int64_t y=0; y<target->cols;y++){
                target->at<uint8_t>(x, y) = 255;
            }
            continue;
        }
        for (int64_t y=0; y<target->cols;y++){
            ySource = (y + yOffset)*scalingFactor;
            if (ySource < 0 || ySource >= source->cols){
                target->at<uint8_t>(x, y) = 255;
                continue;
            }
            target->at<uint8_t>(x, y) = interpolation(source, xSource, ySource);


        }
    }
};

/*
void rotation(Mat* source, Mat* target ){
    float xSource, ySource;
    for (int64_t x=0; x<target->rows;x++){
        for (int64_t y=0; y<target->cols;y++){

        }
    }
}
*/


void lab05_transformation(){
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

	Mat transformedMat(img.rows, img.cols, CV_8UC1);
		// create a Window for display
	//namedWindow("Display window", WINDOW_AUTOSIZE);

	for(;;){

		// acquire camera image
		cap >> img;

		// redo acquisition when image empty
		if (img.empty()) continue;

		// convert img -> gray
		cvtColor(img, gray, CV_BGR2GRAY);

        translationScaling(&gray, &transformedMat, 100, 800, 0.5);

        //cout << "print matrixes" << endl;
		// display image on screen
        imshow("original", gray);
        imshow("transformed", transformedMat);
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


#endif // LAB05_INCLUDED
