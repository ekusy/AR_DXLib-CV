#pragma once
#include "DxLib.h"
#include "IMAGE.h"
#include "Position.h"
#include <math.h>
class dxFunc
{
private:
	int cvImage;
	BASEIMAGE BaseImage;
	int ModelHandle;
public:
	dxFunc();
	~dxFunc();

	void setBaseImage(IMAGE image);
	void createGraphHandle();
	int getCVImage();
	Position getScreenPos(int _modelHandle);
	Position setWorldPos(Position _pos);
	void modelRotateX(int _modelHandle, float _ang);
	void modelRotateZ(int _modelHandle, float _ang);
};

