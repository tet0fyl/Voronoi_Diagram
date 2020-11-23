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
    int numberOfPoint = 2;
    int imgCols = 50;
    int imgRows = 50;

    // VARIABLE
    Point points[numberOfPoint];
    cv::Mat img(imgRows, imgCols, CV_8UC3);

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

    //DRAW VORONOI ARRAY
    int pixelCol = -1;
    int pixelRow = -1;
    for(int i=0; i < (imgRows * imgCols); i++) {
        cout << "DRAW PIXELS : " << (int)((double)i / (double)((imgRows * imgCols) - 1 ) * 100) << " %\r";
        if(i % imgCols == 0) {
            pixelCol = -1;
            pixelRow++;
        }
        pixelCol++;
        Point nearest;
        double minLoss = -1;
        for(int j = 0; j < numberOfPoint; j++) {
            //LOSS
            double loss = sqrt((pixelCol - points[j].x) * (pixelCol - points[j].x) + (pixelRow - points[j].y) * (pixelRow - points[j].y));
            //double loss = abs(pixelCol - points[j].x) + abs(pixelRow - points[j].y);
            //double loss = (abs(pixelCol - points[j].x) > abs(pixelRow - points[j].y))?abs(pixelCol - points[j].x):abs(pixelRow - points[j].y);
            if(minLoss < 0 || minLoss > loss){
                minLoss = loss;
                nearest = points[j];
            };
        }
        if(pixelCol == nearest.x && pixelRow == nearest.y) {
            img.at<cv::Vec3b>(pixelRow, pixelCol)[0] = 0;
            img.at<cv::Vec3b>(pixelRow, pixelCol)[1] = 0;
            img.at<cv::Vec3b>(pixelRow, pixelCol)[2] = 0;
            continue;
        }
        img.at<cv::Vec3b>(pixelRow, pixelCol)[0] = nearest.colors[0];
        img.at<cv::Vec3b>(pixelRow, pixelCol)[1] = nearest.colors[1];
        img.at<cv::Vec3b>(pixelRow, pixelCol)[2] = nearest.colors[2];
    }

    cout << endl;
    cout << "PROCESS FINISH" << endl;
    cv::imshow("Brut Force Voronoï", img);
    cv::waitKey(0);

    return EXIT_SUCCESS;
}