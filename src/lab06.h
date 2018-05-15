#ifndef LAB06_H_INCLUDED
#define LAB06_H_INCLUDED

#include "headers.h"

using namespace std;
using namespace cv;

bool compareArea(KeyPoint a, KeyPoint b){
    return a.size > b.size;
}

Mat calcSimilarityMatrix(vector<Point2f> r, vector<Point2f> b){
    double A, B, tx, ty, z, n;

    // A = ((x1-x2)*(x1d-x2d)+(y1-y2)*(y1d-y2d))/((y1d-y2d)*(y1d-y2d) + (x1d-x2d)*(x1d-x2d))
    z = (r[0].x-r[1].x) * (b[0].x-b[1].x) + (r[0].y-r[1].y) * (b[0].y-b[1].y);
    n = (b[0].y-b[1].y) * (b[0].y-b[1].y) + (b[0].x-b[1].x) * (b[0].x-b[1].x);


//    A = ((r[0].x-r[2].x)*(b[0].x-b[1].x)+(r[1].y-r[2].y)*(b[0].y-b[1].y))/((b[0].y-b[1].y)*(b[0].y-b[1].y) + (b[0].x-b[1].x)*(b[0].x-b[1].x));
    A = z/n;
    B = (r[0].x - r[1].x)/(b[1].y - b[0].y) - A*(b[0].x - b[1].x)/(b[1].y - b[0].y);

    tx = r[0].x - b[0].x * A + b[0].y * B;
    ty = r[0].y - b[0].x * B - b[0].y * A;

    Mat result(3, 3, CV_32FC1);
    result.at<float>(0, 0) = (float) A;
    result.at<float>(0, 1) = (float) -B;
    result.at<float>(0, 2) = (float) tx;
    result.at<float>(1, 0) = (float) B;
    result.at<float>(1, 1) = (float) A;
    result.at<float>(1, 2) = (float) ty;
    result.at<float>(2, 0) = (float) 0;
    result.at<float>(2, 1) = (float) 0;
    result.at<float>(2, 2) = (float) 1;
    cout << "[" << result.at<float>(0, 0) << "|" << result.at<float>(0, 1) << "|" << result.at<float>(0, 2) << "]" << endl;
    cout << "[" << result.at<float>(1, 0) << "|" << result.at<float>(1, 1) << "|" << result.at<float>(1, 2) << "]" << endl;
    cout << "[" << result.at<float>(2, 0) << "|" << result.at<float>(2, 1) << "|" << result.at<float>(2, 2) << "]" << endl;
    return result;
}


void lab_06(void){
   	VideoCapture cap(0);

	if(!cap.isOpened()){
		cout << "Keine Kamera" << endl;
	}
	int key;
	double factor(1);
	Mat img;
	cap >> img;
	Mat gray(img.rows, img.cols, CV_8UC1);
	Mat blackwhite(img.rows, img.cols, CV_8UC1);
	Mat screenShot;
    bool firstRun = true;
    SimpleBlobDetector::Params params;
    params.minArea = 100;
    params.maxArea = 10000000;
    params.filterByArea = true;
    params.filterByCircularity = false;
    params.blobColor = 0;
    params.filterByConvexity = false;
    params.filterByInertia = false;
    params.minDistBetweenBlobs = 10;


    vector<KeyPoint> blobPoints, refPoints;
    vector<Point2f> blobPointer(2);
    vector<Point2f> refPointer(2);


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
        for (int i=0;i<2;i++){
            circle(gray, blobPoints[i].pt, 5,Scalar(255, 255, 255));//, int thickness=1, int lineType=LINE_8, int shift=0 );
        }


		// display image on screen
        imshow("original", gray);

		// berechnung der Translationsmatrix
		if (!firstRun){
            imshow("screenshot", screenShot);
            cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);
            detector->detect( img, blobPoints );
            sort(blobPoints.begin(), blobPoints.end(), compareArea);

            blobPointer[0] = blobPoints[0].pt;
            blobPointer[1] = blobPoints[1].pt;
            //Mat transMatrix = cv::estimateAffine2D(refPointer, blobPointer);
            Mat transMatrix = calcSimilarityMatrix(refPointer, blobPointer);

            Mat transImage(gray.size(), gray.type());

            warpPerspective(img, transImage, transMatrix, transImage.size());

            for (int i=0;i<2;i++){
                circle(transImage, blobPoints[i].pt, 5,Scalar(0, 255, 0));//, int thickness=1, int lineType=LINE_8, int shift=0 );
            }

            imshow("blobs", transImage);


		}


		// wait 30ms for key
		key = waitKey(30);
		if (key == -1){			//do nothing

		} else if(key>=97){		//referenzbild erzeugen
            firstRun = false;
            screenShot = gray.clone();
            cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);
            detector->detect( screenShot, refPoints );
            sort(refPoints.begin(), refPoints.end(), compareArea);
            refPointer[0] = refPoints[0].pt;
            refPointer[1] = refPoints[1].pt;
            for (int i=0;i<2;i++){
                circle(screenShot, refPoints[i].pt, 5,Scalar(255, 255, 255));//, int thickness=1, int lineType=LINE_8, int shift=0 );
            }

        } else {				//close
			break;
		}

	}


}


#endif // LAB06_H_INCLUDED
