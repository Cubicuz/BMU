#ifndef LAB04_H_INCLUDED
#define LAB04_H_INCLUDED

#include "headers.h"

void lab04_createSegmentMat(Mat* blackWhite, Mat* segmenting){
    uint32_t segmentCounter = 0;
    for (uint64_t x=0;x<blackWhite->rows; x++){
        for (uint64_t y=0;y<blackWhite->cols;y++){
            if (blackWhite->at<uint8_t>(x, y) == 255){
                uint32_t smalestSurroundingSegment = 0xFFFFFFFF;
                if (y != 0){
                    //[ ][x][ ]
                    //[ ][0][ ]
                    //[ ][ ][ ]
                    if ((segmenting->at<uint16_t>(x, y-1) != 0 ) && (segmenting->at<uint16_t>(x, y-1) < smalestSurroundingSegment)){
                        smalestSurroundingSegment = segmenting->at<uint16_t>(x, y-1);
                    }
                    if (x != 0){
                        //[x][ ][ ]
                        //[ ][0][ ]
                        //[ ][ ][ ]
                        if ((segmenting->at<uint16_t>(x-1, y-1) != 0 ) && (segmenting->at<uint16_t>(x-1, y-1) < smalestSurroundingSegment)){
                            smalestSurroundingSegment = segmenting->at<uint16_t>(x-1, y-1);
                        }
                    }
                    if (x != blackWhite->rows-1){
                        //[ ][ ][x]
                        //[ ][0][ ]
                        //[ ][ ][ ]
                        if ((segmenting->at<uint16_t>(x+1, y-1) != 0 ) && (segmenting->at<uint16_t>(x+1, y-1) < smalestSurroundingSegment)){
                            smalestSurroundingSegment = segmenting->at<uint16_t>(x+1, y-1);
                        }

                    }
                }
                if (x != 0){
                    //[ ][ ][ ]
                    //[x][0][ ]
                    //[ ][ ][ ]
                    if ((segmenting->at<uint16_t>(x-1, y) != 0 ) && (segmenting->at<uint16_t>(x-1, y) < smalestSurroundingSegment)){
                        smalestSurroundingSegment = segmenting->at<uint16_t>(x-1, y);
                    }
                }

            }
        }
    }
};

void lab04_minimizeSegments(Mat* segmentMat){
    uint16_t posNow, posCheck;
    int8_t didSomethingChange = 1;
    while (didSomethingChange == 1){
        didSomethingChange = 0;
        for (uint64_t x=0;x<segmentMat->rows;x++){
            for (uint64_t y=0;y<segmentMat->cols;y++){
                // zuweisung und test auf ungleich 0
                if (posNow = segmentMat->at<uint16_t>(x, y)){
                    if (y!=0){
                        if (segmentMat->at<uint16_t>(x, y-1) > posNow){
                            segmentMat->at<uint16_t>(x, y) = posNow = segmentMat->at<uint16_t>(x, y-1);
                            didSomethingChange++;
                        }
// geht so noch net, der Fall y!=segmentMat->cols ist noch nicht behandelt
                        if (x!=0) {
                            if (segmentMat->at<uint16_t>(x-1, y) > posNow){
                                segmentMat->at<uint16_t>(x, y) = posNow = segmentMat->at<uint16_t>(x-1, y);
                            }
                            if (segmentMat->at<uint16_t>(x-1, y-1) > posNow){
                                segmentMat->at<uint16_t>(x, y) = posNow = segmentMat->at<uint16_t>(x-1, y-1);
                            }
                            if (segmentMat->at<uint16_t>(x-1, y+1) > posNow){
                                segmentMat->at<uint16_t>(x, y) = posNow = segmentMat->at<uint16_t>(x-1, y+1);
                            }
                        }

                        if (x!=segmentMat->rows){
                            if (segmentMat->at<uint16_t>(x+1, y) > posNow){
                                segmentMat->at<uint16_t>(x, y) = posNow = segmentMat->at<uint16_t>(x+1, y);
                            }
                            if (segmentMat->at<uint16_t>(x+1, y-1) > posNow){
                                segmentMat->at<uint16_t>(x, y) = posNow = segmentMat->at<uint16_t>(x+1, y-1);
                            }
                            if (segmentMat->at<uint16_t>(x+1, y+1) > posNow){
                                segmentMat->at<uint16_t>(x, y) = posNow = segmentMat->at<uint16_t>(x+1, y+1);
                            }
                        }
                    }
                }
            }
        }
    }
};

void lab04_segmentation(void){
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
	Mat blackWhiteMat, segmentationMat, colorMat;
	blackWhiteMat = Mat(img.rows, img.cols, CV_8UC1);
    segmentationMat = Mat(img.rows, img.cols, CV_16UC1);
    colorMat = Mat(img.rows, img.cols, CV_8UC3);
    //cout << "all matrixes created" << endl;

	for(;;){

		// acquire camera image
		cap >> img;

		// redo acquisition when image empty
		if (img.empty()) continue;

		// convert img -> gray
		cvtColor(img, gray, CV_BGR2GRAY);


		for(int x=0;x<gray.rows;x++){

			for(int y=0;y<gray.cols;y++){
                if (gray.at<uint8_t>(x, y) > 127){
                    blackWhiteMat.at<uint8_t>(x, y) = 255;
                }else{
                    blackWhiteMat.at<uint8_t>(x, y) = 0;
                }
			}
		}



        imshow("original", img);

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


#endif // LAB04_H_INCLUDED
