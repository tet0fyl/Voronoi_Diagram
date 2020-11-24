//
// Created by Théophile BRAYE on 23/11/2020.
//
#include "A_BrutForce.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

class Point {
    public:
        int x, y;
        uchar colors[3];
};

int brutForce() {
    cout << "############################" << endl;
    cout << "Diagramme de Voronoï discret" << endl;
    cout << "Algorithme de force brute" << endl;
    cout << "############################" << endl;

    // MACRO
    int numberOfPoint = 5;
    int imgCols = 100;
    int imgRows = 100;

    // VARIABLE FOR POINT GENERATING
    Point points[numberOfPoint];

    // GENERATE POINTS
    for(int i = 0; i < numberOfPoint; i++) {
        cout << "GENERATE " << numberOfPoint << " POINTS : " << (int)((double)i/(double)(numberOfPoint-1)*100)<< " %\r";
        bool isPointPositionAlreadyExist;
        do{
            isPointPositionAlreadyExist = false;
            points[i].x = rand() % imgCols + 1;
            points[i].y = rand() % imgRows + 1;
            for(int j=0; j < i; j++) {
                if(points[i].x == points[j].x && points[i].y == points[j].y) {
                    isPointPositionAlreadyExist = true;
                    break;
                }
            }
        } while(isPointPositionAlreadyExist);
        points[i].colors[0] = (uchar)(rand() % 256);
        points[i].colors[1] = (uchar)(rand() % 256);
        points[i].colors[2] = (uchar)(rand() % 256);
    };
    cout << endl;

    // VARIABLE FOR VORONOI ARRAY DRAWING
    int pixelCol = -1;
    int pixelRow = -1;
    string distanceFormulaLabel[3] = {"Distance Euclidienne","Distance de Manhattan","Distance de Tchebychev"};
    double minLoss[3], loss[3];
    cv::Mat images[3] = {cv::Mat(imgRows, imgCols, CV_8UC3),cv::Mat(imgRows, imgCols, CV_8UC3),cv::Mat(imgRows, imgCols, CV_8UC3)};
    Point nearest[3];

    // DRAW VORONOI ARRAY
    for(int i=0; i < (imgRows * imgCols); i++) {
        cout << "DRAW PIXELS : " << (int)((double)i / (double)((imgRows * imgCols) - 1 ) * 100) << " %\r";
        if(i % imgCols == 0) {
            pixelCol = -1;
            pixelRow++;
        }
        pixelCol++;
        minLoss[0] = -1.0, minLoss[1] = -1.0, minLoss[2] = -1.0 ;
        for(int j = 0; j < numberOfPoint; j++) {
            //LOSS
            //Euclidienne
            loss[0] = sqrt((pixelCol - points[j].x) * (pixelCol - points[j].x) + (pixelRow - points[j].y) * (pixelRow - points[j].y));
            //Manhattan
            loss[1] = abs(pixelCol - points[j].x) + abs(pixelRow - points[j].y);
            //Tchebychev
            loss[2] = (abs(pixelCol - points[j].x) > abs(pixelRow - points[j].y))?abs(pixelCol - points[j].x):abs(pixelRow - points[j].y);

            for(int k = 0; k < 3; k++ ) {
                if(minLoss[k] < 0 || minLoss[k] > loss[k]){
                    minLoss[k] = loss[k];
                    nearest[k] = points[j];
                };
            }
        }
        for(int k = 0; k < 3; k++) {
            if(pixelCol == nearest[k].x && pixelRow == nearest[k].y) {
                images[k].at<cv::Vec3b>(pixelRow, pixelCol)[0] = 0;
                images[k].at<cv::Vec3b>(pixelRow, pixelCol)[1] = 0;
                images[k].at<cv::Vec3b>(pixelRow, pixelCol)[2] = 0;
                continue;
            }
            images[k].at<cv::Vec3b>(pixelRow, pixelCol)[0] = nearest[k].colors[0];
            images[k].at<cv::Vec3b>(pixelRow, pixelCol)[1] = nearest[k].colors[1];
            images[k].at<cv::Vec3b>(pixelRow, pixelCol)[2] = nearest[k].colors[2];
        }
    }

    cout << endl;
    cout << "PROCESS FINISH" << endl;
    for(int k = 0; k < 3; k++){
        cv::imshow("Brut Force Voronoï : " + distanceFormulaLabel[k], images[k]);
    }
    cv::waitKey(0);

    return EXIT_SUCCESS;
}