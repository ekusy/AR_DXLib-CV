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

