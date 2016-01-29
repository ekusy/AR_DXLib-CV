#include "cvFunc.h"


cvFunc::cvFunc()
{
	if (!cap.open(1))
		cap.open(0);
}

cvFunc::~cvFunc()
{
}

void cvFunc::readCapture(bool _showFlg){
	cap >> frame;
	if (_showFlg == true){
		imshow("cap", frame);
	}
	cvtColor(frame, hsv, CV_BGR2HSV);
}

void cvFunc::setImage(Mat _source){
	image = _source;
}

IplImage cvFunc::getFrameHandle(){
	return frame;
}

IMAGE cvFunc::getImageData(){
	IMAGE IMG;
	IplImage tmp = image;
	IMG.imageData = tmp.imageData;
	IMG.width = tmp.width;
	IMG.height = tmp.height;
	IMG.widthStep = tmp.widthStep;

	return IMG;
}

Position cvFunc::getPosition(bool _noiseFlg){
	Position pos;
	int count = 0;
	int X = 0;
	int Y = 0;
	Mat mask(hsv.rows, hsv.cols, CV_8UC3);
	mask = Scalar(0, 0, 0);
	//Mat mask


	
	for (int row = 0; row < hsv.rows; row++){
		for (int col = 0; col < hsv.cols; col++){
			int num = hsv.step*row + col*hsv.channels();
			int color[] = { hsv.data[num], hsv.data[num + 1], hsv.data[num + 2] };
			if (judgeColor(color, 100, 110, 130, 255, 100, 255)){
				//num = mask.step*row + col;
				//mask.data[num] = 255;
				frame.data[num] = 255;
				frame.data[num + 1] = 0;
				frame.data[num + 2] = 0;

				count++;
				Y += row;
				X += col;
			}
			else{
				//num = mask.step*row + col;
				//mask.data[num] = 100;
				
				//frame.data[num] = 255;
				//frame.data[num + 1] = 255;
				//frame.data[num + 2] = 255;
				
			}
		}
	}
	
	/*
	else{
		for (int row = 0; row < hsv.rows; row++){
			for (int col = 0; col < hsv.cols; col++){
				int num = hsv.step*row + col*hsv.channels();
				int color[] = { hsv.data[num], hsv.data[num + 1], hsv.data[num + 2] };
				if ((judgeColor(color, 100, 110, 130, 255, 100, 255))){
					mask.data[num] = 255;
				}
				else{
					mask.data[num] = 0;
				}
			}
		}
		//erode(mask, mask, Mat(), Point(-1, -1),2);
		//dilate(mask, mask, Mat(), Point(-1, -1), 2);
		for (int row = 0; row < hsv.rows; row++){
			for (int col = 0; col < hsv.cols; col++){
				int num = hsv.step*row + col*hsv.channels();
				if (mask.data[num] == 255){
					countR++;
					red.y += row;
					red.x += col;

					frame.data[num] = 255;
					frame.data[num + 1] = 0;
					frame.data[num + 2] = 0;
				}
				else{
					//num = mask.step*row + col;
					//mask.data[num] = 100;
					//frame.data[num] = 255; frame.data[num + 1] = 255;	frame.data[num + 2] = 255;

				}
			}
		}
	}

	*/

	if (count > 20){
		X /= count;
		Y /= count;
	}
	image = frame;
	if (count <= 20){ //|| countB <= 20){
		X = -1;
		Y = -1;
	}
	else{
		pos.x = X;
		pos.y = Y;
	}
	return pos;
}

bool cvFunc::judge(int source, int min, int max) {
	if (min == max)
		return true;
	if (min > max) {
		if (source >= max || source <= min)
			return true;
	}
	else {
		if (source >= min && source <= max)
			return true;
	}
	return false;
}

bool cvFunc::judgeColor(int source[], int h_min, int h_max, int s_min, int s_max, int v_min, int v_max) {
	int count = 0;
	if (judge(source[0], h_min, h_max))
		count++;
	if (judge(source[1], s_min, s_max))
		count++;
	if (judge(source[2], v_min, v_max))
		count++;

	if (count == 3)
		return true;
	else
		return false;
}

double cvFunc::getAngle(){
	return (atan2(double(blue.y - red.y), double(blue.x - red.x)));
}