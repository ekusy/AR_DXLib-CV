#include "main.h"


main::main()
{
}


main::~main()
{
}

static const float ROTATE_SPEED = DX_PI_F / 90;//回転スピード

// (x,y)の点を(mx,my)を中心にang角回転する
void rotate(float *x, float *y, const float ang, const float mx, const float my){
	const float ox = *x - mx, oy = *y - my;
	*x = ox * cos(ang) + oy * sin(ang);
	*y = -ox * sin(ang) + oy * cos(ang);
	*x += mx;
	*y += my;
}
// プログラムは WinMain から始まります
	int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
		ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
		cvFunc CV;
		dxFunc DX;
		float cameraX = 0, cameraZ = -20;    //カメラの座標
		const float targetX = 0, targetZ = 0;//カメラの視線の先ターゲットの座標

		//3Dモデルの読み込み
		int ModelHandle = MV1LoadModel("./model/bokoboko.pmd");
		//奥行0.1～1000までをカメラの描画範囲とする
		SetCameraNearFar(0.1f, 1000.0f);

		while (ProcessMessage() == 0){

			CV.readCapture();
			DX.setBaseImage(CV.getImageData());
			DX.createGraphHandle();
			// フレームの内容を画面に描画
			DrawGraph(0, 0, DX.getCVImage(), FALSE);

			if (CheckHitKey(KEY_INPUT_LEFT) > 0){//左キーが押されていたら
				rotate(&cameraX, &cameraZ, +ROTATE_SPEED, targetX, targetZ);//回転
			}
			if (CheckHitKey(KEY_INPUT_RIGHT) > 0){//右キーが押されていたら
				rotate(&cameraX, &cameraZ, -ROTATE_SPEED, targetX, targetZ);//回転
			}

			//第一引数の視点から第二引数のターゲットを見る角度にカメラを設置
			SetCameraPositionAndTarget_UpVecY(VGet(cameraX, 10, cameraZ), VGet(targetX, 10.0f, targetZ));

			// ３Ｄモデルの描画
			MV1DrawModel(ModelHandle);

			// 裏画面の内容を表画面に反映
			ScreenFlip();
		}

		CV.cap.release();
		DxLib_End();
		return 0;				// ソフトの終了 
}