//openCV
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
//metaBall
#include <string>
#include "BezierObject.h"


using namespace std;
using namespace cv;


int main() {
    Ball bb,bb2;
    bb.setCenter(Dot(80, 300));
    bb.setRadius(50.0);
    bb.setCurveDotAmount(50);
    bb.update();
    std::vector<Dot> b1Curve = bb.getCurve();

    bb2.setCenter(Dot(500, 350));
    bb2.setRadius(150.0);
    bb2.setCurveDotAmount(50);
    bb2.update();
    std::vector<Dot> b2Curve = bb2.getCurve();

    BezierObject bez;
    bez.setCurveDotAmount(20);
    std::vector<Dot> bezCurve;
    bez.setControlDotsFromBall(bb, bb2);
    bezCurve = bez.getCurves();


    cv::Size videoSize = Size(1500, 700);
    //空白畫布
    Mat img = Mat::zeros(videoSize, CV_8UC3);
    //img.setTo(255);//將畫布設為白色
    
    //cv::VideoWriter writer;
    //writer.open("VideoTest.mp4", VideoWriter::fourcc('H', '2', '6', '4'), 30, videoSize);
    

    for (int m = 0; m < 200; m++)
    {
        img = Mat::zeros(videoSize, CV_8UC3);
        bb.moveCenter(5, 0);
        bb.update();
        b1Curve = bb.getCurve();

        bez.setControlDotsFromBall(bb, bb2);
        bezCurve = bez.getCurves();
        for (int i = 0; i < b1Curve.size(); i++)
        {
            line(img, Point(b1Curve[i].GetPositionX(), b1Curve[i].GetPositionY()), Point(b1Curve[( i + 1 ) % b1Curve.size()].GetPositionX(), b1Curve[( i + 1 ) % b1Curve.size()].GetPositionY()), Scalar(0, 0, 255), 5);
            line(img, Point(b2Curve[i].GetPositionX(), b2Curve[i].GetPositionY()), Point(b2Curve[( i + 1 ) % b2Curve.size()].GetPositionX(), b2Curve[( i + 1 ) % b2Curve.size()].GetPositionY()), Scalar(0, 0, 255), 5);
        }
        for (int i = 0; i < bezCurve.size(); i++)
        {
            line(img, Point(bezCurve[i].GetPositionX(), bezCurve[i].GetPositionY()), Point(bezCurve[( i + 1 ) % bezCurve.size()].GetPositionX(), bezCurve[( i + 1 ) % bezCurve.size()].GetPositionY()), Scalar(0, 0, 255), 5);

        }
        //writer.write(img);
        imshow("show image", img);
        waitKey(30);
    }

    waitKey();
    return 0;
}