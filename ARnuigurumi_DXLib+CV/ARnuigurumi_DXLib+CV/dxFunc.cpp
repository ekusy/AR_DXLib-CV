#include "dxFunc.h"


dxFunc::dxFunc()
{
	// BASEIMAGE �\���̂��O�ŏ�����
	memset(&BaseImage, 0, sizeof(BASEIMAGE));
	//MV1SetUseZBuffer(ModelHandle, false);
	// �J���[�t�H�[�}�b�g�͕ω����Ȃ��̂ōŏ��ɐݒ�
	CreateFullColorData(&BaseImage.ColorData);

	// �~�b�v�}�b�v�ł͂Ȃ��̂łO
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
	// �O���t�B�b�N�n���h�����쐬���Ă��邩�ǂ����ŏ����𕪊�
	if (cvImage == -1)
	{
		// �ŏ��̏ꍇ�̓O���t�B�b�N�n���h���̍쐬�Ɖf���̓]������x�ɍs��
		cvImage = CreateGraphFromBaseImage(&BaseImage);
	}
	else
	{
		// �Q��ڈȍ~�̓O���t�B�b�N�n���h���։f����]��
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
