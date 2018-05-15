#ifndef LAB07_H_INCLUDED
#define LAB07_H_INCLUDED

#include "headers.h"

using namespace std;
using namespace cv;

Mat calcPerspectiveMatrix(vector<Point2f> r, vector<Point2f> b){

}

void lab_07(void){
   	VideoCapture cap(0);

	if(!cap.isOpened()){
		cout << "Keine Kamera" << endl;
	}
	int key;
	double factor(1);
	Mat img, imgcpy;
	cap >> img;
	Mat gray(img.rows, img.cols, CV_8UC1);
	Mat blackwhite(img.rows, img.cols, CV_8UC1);
	Mat screenShot;
    bool firstRun = true;
    SimpleBlobDetector::Params params;
    params.minArea = 50;
    params.maxArea = 10000000;
    params.filterByArea = true;
    params.filterByCircularity = false;
    params.blobColor = 0;
    params.filterByConvexity = false;
    params.filterByInertia = false;
    params.minDistBetweenBlobs = 10;


    vector<KeyPoint> blobPoints, refPoints;
    vector<Point2f> blobPointer(4);
    vector<Point2f> refPointer(4);
    vector<Scalar> myColors(4);
    myColors[0] = Scalar(255, 255, 255);
    myColors[1] = Scalar(255, 0, 0);
    myColors[2] = Scalar(0, 255, 0);
    myColors[3] = Scalar(0, 0, 255);


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

        // convert gray -> blackWhite
        cvtGrayToBW(gray, blackwhite);

        cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);
        detector->detect( img, blobPoints );
        sort(blobPoints.begin(), blobPoints.end(), compareArea);
        imgcpy = img.clone();
        for (int i=0;i<4;i++){
            circle(imgcpy, blobPoints[i].pt, 5,myColors[i]);//, int thickness=1, int lineType=LINE_8, int shift=0 );
        }


		// display image on screen
        imshow("original", imgcpy);

		// berechnung der Translationsmatrix
		if (!firstRun){
            imshow("screenshot", screenShot);
            cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);
            detector->detect( img, blobPoints );
            sort(blobPoints.begin(), blobPoints.end(), compareArea);

            blobPointer[0] = blobPoints[0].pt;
            blobPointer[1] = blobPoints[1].pt;
            blobPointer[2] = blobPoints[2].pt;
            blobPointer[3] = blobPoints[3].pt;

//            Mat transMatrix = calcSimilarityMatrix(refPointer, blobPointer);
            Mat transMatrix = getPerspectiveTransform(blobPointer, refPointer);

            Mat transImage(gray.size(), gray.type());

            warpPerspective(img, transImage, transMatrix, transImage.size());

            for (int i=0;i<4;i++){
                circle(transImage, blobPoints[i].pt, 5,myColors[i]);//, int thickness=1, int lineType=LINE_8, int shift=0 );
            }

            imshow("blobs", transImage);


		}


		// wait 30ms for key
		key = waitKey(30);
		if (key == -1){			//do nothing

		} else if(key>=97){		//referenzbild erzeugen
            firstRun = false;
            screenShot = img.clone();
            cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);
            detector->detect( screenShot, refPoints );
            sort(refPoints.begin(), refPoints.end(), compareArea);
            refPointer[0] = refPoints[0].pt;
            refPointer[1] = refPoints[1].pt;
            refPointer[2] = refPoints[2].pt;
            refPointer[3] = refPoints[3].pt;
            for (int i=0;i<4;i++){
                circle(screenShot, refPoints[i].pt, 5,myColors[i]);//, int thickness=1, int lineType=LINE_8, int shift=0 );
            }

        } else {				//close
			break;
		}

	}


}




#endif // LAB07_H_INCLUDED
