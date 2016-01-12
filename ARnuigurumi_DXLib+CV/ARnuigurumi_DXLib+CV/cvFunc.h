#pragma once
#include "opencv2\opencv.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "IMAGE.h"
#include "Position.h"
using namespace cv;
class cvFunc
{
private:
	Mat image;
	Mat frame;
	Mat hsv;
	Position red, blue;
public:
	VideoCapture cap;
	cvFunc();
	~cvFunc();
	void readCapture(bool _showFlg);
	void setImage(Mat _source);
	IplImage getFrameHandle(void);
	IMAGE getImageData(void);
	Position getPosition(bool noiseFlg);
	bool judge(int source, int min, int max);
	bool judgeColor(int source[], int h_min, int h_max, int s_min, int s_max, int v_min, int v_max);
	double getAngle(void);
};

