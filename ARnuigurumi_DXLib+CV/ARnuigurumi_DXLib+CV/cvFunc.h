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
public:
	VideoCapture cap;
	cvFunc();
	~cvFunc();
	void readCapture(void);
	void setImage(Mat _source);
	IplImage getFrameHandle(void);
	IMAGE cvFunc::getImageData(void);
	Position getPosition(void);
	bool hsvJudge(int color[3], int h, int h_field, int s, int s_field, int v, int v_field);
};

