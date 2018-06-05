// opencv includes
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>

// c++ includes
#include <iostream>     // for std::strstream

// local includes
#include "Gradient.h"

using namespace cv;
using namespace std;

//-------------------------------------------
// main routine of the program
//-------------------------------------------
int main(int argc, char *argv[])
{
    Mat cameraImage;
    Mat grayImage;
    Mat gradientImage;
    Mat line1, line2, line3;
    Mat line1a, line1b, line2a, line2b, line3a, line3b;
    Mat finalImage;
    int width, height;
    int i, j, k;
    int binWidth;
    int binHeight;
    int maxHeight;
    int deltawidth, deltaheight;
    bool firstRun;
    double maxhist;
    Mat tiles[4][3];
    Mat tilesHoG[4][3];
    Gradient gradient[4][3];

    // try to open the default camera
    VideoCapture cap(0);

    // check if camera is present
    if(!cap.isOpened())
    {
        cout << "Error opening camera! Exiting program..." << endl;
        waitKey(0);
        return(-1);
    }

    // loop for camera acquistion and processing
    firstRun = true;
    for(;;)
    {
        // capture camera frame
        cap >> cameraImage;
        if(cameraImage.empty()) continue;

        if(firstRun)
        {
            firstRun = false;
            width = cameraImage.size().width;
            height = cameraImage.size().height;

            // define size of histogram bins
            binWidth = width / 4 / HISTOGRAM_BINS;
            maxHeight = 50 / 3;
            deltawidth = width / 4;
            deltaheight = height / 3;
        }

        // convert camera image from color to grayscale
        cvtColor(cameraImage, grayImage, CV_BGR2GRAY);
        normalize(grayImage, grayImage, 0, 255, NORM_MINMAX, CV_8UC1);

        for(i = 0; i < 4; i++)
        {
            for(j = 0; j < 3; j++)
            {
                Range Range_x(i * deltawidth, (i + 1) * deltawidth);
                Range Range_y(j * deltaheight, (j + 1) * deltaheight);
                tiles[i][j] = grayImage(Range_y, Range_x).clone();
                gradient[i][j].calcGradient(tiles[i][j].data, deltawidth, deltaheight, 5);
                unsigned char* datapointer = gradient[i][j].getGradient();
                Mat tmpImage(deltaheight, deltawidth, CV_8U, datapointer);
                cvtColor(tmpImage, tilesHoG[i][j], CV_GRAY2BGR);

                for(k = 0; k < HISTOGRAM_BINS; k++)
                {
                    maxhist = gradient[i][j].getHistogramMax();
                    if(maxhist > 0.0)
                    {
                        binHeight = maxHeight * gradient[i][j].getHistogram(k) / maxhist;
                        Point startPoint(k * binWidth, height/3 - binHeight);
                        Point endPoint((k + 1) * binWidth - 2, height/3);
                        rectangle(tilesHoG[i][j], startPoint, endPoint, Scalar(0,255,0), CV_FILLED);
                    }
                }
            }
        }

        hconcat(tilesHoG[0][0], tilesHoG[1][0], line1a);
        hconcat(tilesHoG[2][0], tilesHoG[3][0], line1b);
        hconcat(line1a, line1b, line1);
        hconcat(tilesHoG[0][1], tilesHoG[1][1], line2a);
        hconcat(tilesHoG[2][1], tilesHoG[3][1], line2b);
        hconcat(line2a, line2b, line2);
        hconcat(tilesHoG[0][2], tilesHoG[1][2], line3a);
        hconcat(tilesHoG[2][2], tilesHoG[3][2], line3b);
        hconcat(line3a, line3b, line3);
        vconcat(line1, line2, finalImage);
        vconcat(finalImage, line3, finalImage);
        imshow("Gradient", finalImage);

        // exit if key is pressed
        if(waitKey(30)>0) break;
    }

    return 0;
}
