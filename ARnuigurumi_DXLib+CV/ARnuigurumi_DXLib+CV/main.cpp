#include "main.h"


main::main()
{
}


main::~main()
{
}

static const float ROTATE_SPEED = DX_PI_F / 90;//��]�X�s�[�h
double map(double v, double sx, double sn, double dx, double dn)
{
	return (v - sn) * (dx - dn) / (sx - sn) + dn;
}
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
		Position pos;
		float cameraX = 0, cameraZ = 0;    //�J�����̍��W
		const float targetX = 0, targetZ = 0;//�J�����̎����̐�^�[�Q�b�g�̍��W
		float x = 0.0, y = 0.0, z = 0.0;
		//3D���f���̓ǂݍ���
		int ModelHandle = MV1LoadModel("./model/bokoboko.pmd");
		//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
		SetCameraNearFar(0.1f, 1000.0f);
		//�������̎��_����������̃^�[�Q�b�g������p�x�ɃJ������ݒu
		SetCameraPositionAndTarget_UpVecY(VGet(cameraX, 5, cameraZ), VGet(cameraX, 5, cameraZ + 10));
		
		int ang = 0;

		while (ProcessMessage() == 0){
			// ��ʂɕ`����Ă�����̂����S������
			ClearDrawScreen();
			DWORD start = timeGetTime();       // �X�^�[�g����
			CV.readCapture();
			pos = CV.getPosition(false);
			DX.setBaseImage(CV.getImageData());
			DX.createGraphHandle();

			// �t���[���̓��e����ʂɕ`��
			DrawGraph(0, 0, DX.getCVImage(), FALSE);

			if (CheckHitKey(KEY_INPUT_LEFT) > 0){//���L�[��������Ă�����
				x--;
				//rotate(&cameraX, &cameraZ, +ROTATE_SPEED, targetX, targetZ);//��]
			}
			if (CheckHitKey(KEY_INPUT_RIGHT) > 0){//�E�L�[��������Ă�����
				x++;
				//rotate(&cameraX, &cameraZ, -ROTATE_SPEED, targetX, targetZ);//��]
			}
			if (CheckHitKey(KEY_INPUT_UP) > 0){//���L�[��������Ă�����
				y++;
				//rotate(&cameraX, &cameraZ, +ROTATE_SPEED, targetX, targetZ);//��]
			}
			if (CheckHitKey(KEY_INPUT_DOWN) > 0){//�E�L�[��������Ă�����
				y--;
				//rotate(&cameraX, &cameraZ, -ROTATE_SPEED, targetX, targetZ);//��]
			}
			
			if (pos.x != -1){
				pos.x -= 320;
				pos.fx = float(pos.x)/15.0;
				if (pos.fx > 15.0)
					pos.fx = 15.0;
				if (pos.fx < -15.0)
					pos.fx = -15.0;
				//pos.x = map(float(pos.x), -320.0, 320.0, -15.0, 15.0);
				pos.y -= 240;
				pos.fy = float(pos.y) / 10.0;
				if (pos.fy > 10.0)
					pos.fy = 10.0;
				if (pos.fy < -10.0)
					pos.fy = -10.0;
				//pos.y = map(float(pos.y), -240.0, 240.0, -10.0, 10.0);
			}
			
			//pos = DX.setWorldPos(pos);
			//�㉺�}10.0,���E�}15.0
			MV1SetPosition(ModelHandle, VGet(pos.fx, -pos.fy, 20.0f));
			MV1SetRotationXYZ(ModelHandle,VGet( 0.0,0.0,CV.getAngle()) );
			//MV1SetRotationXYZ(ModelHandle, VGet(ang, 0.0, 0.0));
			//MV1SetRotationXYZ(ModelHandle, VGet(rand(),rand(),rand()));
			// �R�c���f���̕`��
			MV1DrawModel(ModelHandle);

			//�o�ߎ���
			DWORD end = timeGetTime();    // �I������
			double time = (double)(end - start) / 1000;
			DrawFormatString(20, 20, GetColor(0, 0, 255), "time = %lf,fps = %lf", time , 1/time);
			DrawFormatString(20, 50, GetColor(0, 0, 255), "x = %lf : y = %lf",pos.fx,pos.fy);
			//pos = DX.getScreenPos(ModelHandle);
			DrawFormatString(20, 70, GetColor(0, 255, 255), "x = %lf : y = %lf", pos.fx, pos.fy);
			DrawFormatString(20, 90, GetColor(255, 255, 0), "angle=%lf", (CV.getAngle()*180.0 / DX_PI));
			// ����ʂ̓��e��\��ʂɔ��f
			ScreenFlip();
			ang++;
			if (ang == 360){
				ang = 0;
			}
		}

		CV.cap.release();
		DxLib_End();
		return 0;				// �\�t�g�̏I�� 
}