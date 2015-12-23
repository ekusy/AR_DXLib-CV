#include "main.h"


main::main()
{
}


main::~main()
{
}

static const float ROTATE_SPEED = DX_PI_F / 90;//��]�X�s�[�h

// (x,y)�̓_��(mx,my)�𒆐S��ang�p��]����
void rotate(float *x, float *y, const float ang, const float mx, const float my){
	const float ox = *x - mx, oy = *y - my;
	*x = ox * cos(ang) + oy * sin(ang);
	*y = -ox * sin(ang) + oy * cos(ang);
	*x += mx;
	*y += my;
}
// �v���O������ WinMain ����n�܂�܂�
	int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
		ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
		cvFunc CV;
		dxFunc DX;
		float cameraX = 0, cameraZ = -20;    //�J�����̍��W
		const float targetX = 0, targetZ = 0;//�J�����̎����̐�^�[�Q�b�g�̍��W

		//3D���f���̓ǂݍ���
		int ModelHandle = MV1LoadModel("./model/bokoboko.pmd");
		//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
		SetCameraNearFar(0.1f, 1000.0f);

		while (ProcessMessage() == 0){

			CV.readCapture();
			DX.setBaseImage(CV.getImageData());
			DX.createGraphHandle();
			// �t���[���̓��e����ʂɕ`��
			DrawGraph(0, 0, DX.getCVImage(), FALSE);

			if (CheckHitKey(KEY_INPUT_LEFT) > 0){//���L�[��������Ă�����
				rotate(&cameraX, &cameraZ, +ROTATE_SPEED, targetX, targetZ);//��]
			}
			if (CheckHitKey(KEY_INPUT_RIGHT) > 0){//�E�L�[��������Ă�����
				rotate(&cameraX, &cameraZ, -ROTATE_SPEED, targetX, targetZ);//��]
			}

			//�������̎��_����������̃^�[�Q�b�g������p�x�ɃJ������ݒu
			SetCameraPositionAndTarget_UpVecY(VGet(cameraX, 10, cameraZ), VGet(targetX, 10.0f, targetZ));

			// �R�c���f���̕`��
			MV1DrawModel(ModelHandle);

			// ����ʂ̓��e��\��ʂɔ��f
			ScreenFlip();
		}

		CV.cap.release();
		DxLib_End();
		return 0;				// �\�t�g�̏I�� 
}