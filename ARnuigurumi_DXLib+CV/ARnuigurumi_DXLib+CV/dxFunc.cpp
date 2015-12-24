#include "dxFunc.h"


dxFunc::dxFunc()
{
	// BASEIMAGE 構造体を０で初期化
	memset(&BaseImage, 0, sizeof(BASEIMAGE));
	//MV1SetUseZBuffer(ModelHandle, false);
	// カラーフォーマットは変化しないので最初に設定
	CreateFullColorData(&BaseImage.ColorData);

	// ミップマップではないので０
	BaseImage.MipMapCount = 0;
	cvImage = -1;

	ModelHandle = MV1LoadModel("./model/bokoboko.pmd");
}


dxFunc::~dxFunc()
{
}

void dxFunc::setBaseImage(IMAGE _image){
	BaseImage.GraphData = _image.imageData;
	BaseImage.Width = _image.width;
	BaseImage.Height = _image.height;
	BaseImage.Pitch = _image.widthStep;
}

void dxFunc::createGraphHandle(){
	// グラフィックハンドルを作成しているかどうかで処理を分岐
	if (cvImage == -1)
	{
		// 最初の場合はグラフィックハンドルの作成と映像の転送を一度に行う
		cvImage = CreateGraphFromBaseImage(&BaseImage);
	}
	else
	{
		// ２回目以降はグラフィックハンドルへ映像を転送
		ReCreateGraphFromBaseImage(&BaseImage, cvImage);
	}
}

int dxFunc::getCVImage(){
	return cvImage;
}

Position dxFunc::getScreenPos(int _modelHandle){
	VECTOR pos;
	Position p;
	pos = ConvWorldPosToScreenPos(MV1GetPosition(_modelHandle));
	p.fx = pos.x;
	p.fy = pos.y;
	return p;
}

Position dxFunc::setWorldPos(Position _pos){
	VECTOR screen;
	VECTOR world;
	Position pos;
	screen.x = double(_pos.x);
	screen.y = double(_pos.y);
	world = ConvScreenPosToWorldPos(screen);
	pos.fx = world.x;
	pos.fy = world.y;
	return pos;
}
