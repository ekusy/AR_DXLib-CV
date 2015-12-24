#include "cvFunc.h"


cvFunc::cvFunc()
{
	if (!cap.open(1))
		cap.open(0);
}


cvFunc::~cvFunc()
{
}

void cvFunc::readCapture(){
	cap >> frame;
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
	if (_noiseFlg){
		for (int row = 0; row < hsv.rows; row++){
			for (int col = 0; col < hsv.cols; col++){
				int num = hsv.step*row + col*hsv.channels();
				if ((hsv.data[num] > 100 && hsv.data[num] < 110) && hsv.data[num + 1] > 130 && hsv.data[num + 2] > 130){
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
					/*
					frame.data[num] = 255;
					frame.data[num + 1] = 255;
					frame.data[num + 2] = 255;
					*/
				}
			}
		}
	}
	else{
		for (int row = 0; row < hsv.rows; row++){
			for (int col = 0; col < hsv.cols; col++){
				int num = hsv.step*row + col*hsv.channels();
				if ((hsv.data[num] > 100 && hsv.data[num] < 110) && hsv.data[num + 1] > 130 && hsv.data[num + 2] > 130){
					mask.data[num] = 255;
				}
				else{
					mask.data[num] = 0;
				}
			}
		}
		erode(mask, mask, Mat(), Point(-1, -1), 4);
		dilate(mask, mask, Mat(), Point(-1, -1), 4);
		for (int row = 0; row < hsv.rows; row++){
			for (int col = 0; col < hsv.cols; col++){
				int num = hsv.step*row + col*hsv.channels();
				if (mask.data[num] == 255){
					count++;
					Y += row;
					X += col;
				}
			}
		}
	}

	
	std::ostringstream oss;

	if (count > 0){
		pos.x = X / count;
		pos.y = Y / count;
		oss << "X=" << pos.x << " Y=" << pos.y;
	}
	else{
		oss << "X=" << -1 << " Y=" << -1;
	}
	String str = oss.str();
	//str += "X=" + std::to_string(int(X / count)) + " Y=" + std::to_string(int(Y / count));
	putText(frame, str, Point(50, 50), FONT_HERSHEY_SIMPLEX, 1,Scalar(0,0,200));
	image = frame;

	return pos;
}

bool cvFunc::hsvJudge(int color[3],int h, int h_field, int s, int s_field, int v, int v_field){
	int judge = 0;
	//if ()
	return true;
}