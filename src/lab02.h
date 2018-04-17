#ifndef LAB02_H_INCLUDED
#define LAB02_H_INCLUDED

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

using namespace std;
using namespace cv;


void lab02(){
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
	Mat brightnessMat, contrastMat, sobelGxMat, sobelGyMat, sobelGMat, sobelGxMatprint, sobelGyMatprint;
	brightnessMat = Mat(img.rows, img.cols, CV_8UC1);
	contrastMat = Mat(img.rows, img.cols, CV_8UC1);
	sobelGxMat = Mat(img.rows, img.cols, CV_16SC1);
	sobelGyMat = Mat(img.rows, img.cols, CV_16SC1);
	sobelGxMatprint = Mat(img.rows, img.cols, CV_8UC1);
	sobelGyMatprint = Mat(img.rows, img.cols, CV_8UC1);
    sobelGMat = Mat(img.rows, img.cols, CV_8UC1);
    //cout << "all matrixes created" << endl;

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
				val=0;
				if (x>0){
                    val += 2*gray.at<unsigned char>(x-1, y);
                    if (y>0){
                        val += gray.at<unsigned char>(x-1, y-1);
                    }
                    if (y<gray.cols-1){
                        val += gray.at<unsigned char>(x-1, y+1);
                    }
				}
				if (x<gray.rows-1){
                    val -= 2*gray.at<unsigned char>(x+1, y);
                    if (y>0){
                        val -= gray.at<unsigned char>(x+1, y-1);
                    }
                    if (y<gray.cols-1){
                        val -= gray.at<unsigned char>(x+1, y+1);
                    }
				}
				sobelGxMat.at<short>(x, y) = val;
                //cout << "sobel x calculated" << endl;

				// gy
				val=0;
				if (y>0){
                    val += 2*gray.at<unsigned char>(x, y-1);
                    if (x>0){
                        val += gray.at<unsigned char>(x-1, y-1);
                    }
                    if (x<gray.rows-1){
                        val += gray.at<unsigned char>(x+1, y-1);
                    }
				}
				if (y<gray.cols-1){
                    val -= 2*gray.at<unsigned char>(x, y+1);
                    if (x>0){
                        val -= gray.at<unsigned char>(x-1, y+1);
                    }
                    if (x<gray.rows-1){
                        val -= gray.at<unsigned char>(x+1, y+1);
                    }
				}
				sobelGyMat.at<short>(x, y) = val;
                //cout << "sobel y calculatet" << endl;

                val = sobelGxMat.at<short>(x, y) * sobelGxMat.at<short>(x, y) + sobelGyMat.at<short>(x, y) * sobelGyMat.at<short>(x, y);
                val = sqrt(val);
                if (val>255){
                    val = 255;
                }
                sobelGMat.at<unsigned char>(x, y) = val;
                //cout << "sobel betrag calculated" << endl;
                sobelGxMatprint.at<unsigned char>(x, y) =(unsigned char) (sobelGxMat.at<short>(x, y) / 8 + 127);
                sobelGyMatprint.at<unsigned char>(x, y) =(unsigned char) (sobelGyMat.at<short>(x, y) / 8 + 127);
			}
		}

		// apply contrast

        //cout << "print matrixes" << endl;
		// display image on screen
		imshow("Display window", sobelGMat);
        imshow("original", img);
//        imshow("Sobel X", sobelGxMatprint);
//        imshow("Sobel Y", sobelGyMatprint);
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

#endif // LAB02_H_INCLUDED
