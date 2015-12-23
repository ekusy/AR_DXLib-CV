#pragma once
#include "opencv2\opencv.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "IMAGE.h"
using namespace cv;
class cvFunc
{
private:
	
	Mat frame;
public:
	VideoCapture cap;
	cvFunc();
	~cvFunc();
	void readCapture(void);
	IplImage getFrameHandle(void);
	IMAGE cvFunc::getImageData(void);
};

