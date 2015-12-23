#pragma once
#include "DxLib.h"
#include "IMAGE.h"
class dxFunc
{
private:
	int cvImage;
	BASEIMAGE BaseImage;

public:
	dxFunc();
	~dxFunc();

	void setBaseImage(IMAGE image);
	void createGraphHandle();
	int getCVImage();
};

