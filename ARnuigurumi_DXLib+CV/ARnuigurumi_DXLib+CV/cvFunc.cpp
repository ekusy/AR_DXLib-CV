#include "cvFunc.h"


cvFunc::cvFunc()
{
	cap.open(0);
}


cvFunc::~cvFunc()
{
}

void cvFunc::readCapture(){
	cap >> frame;
}

IplImage cvFunc::getFrameHandle(){
	return frame;
}

IMAGE cvFunc::getImageData(){
	IMAGE image;
	IplImage tmp = frame;
	image.imageData = tmp.imageData;
	image.width = tmp.width;
	image.height = tmp.height;
	image.widthStep = tmp.widthStep;

	return image;
}