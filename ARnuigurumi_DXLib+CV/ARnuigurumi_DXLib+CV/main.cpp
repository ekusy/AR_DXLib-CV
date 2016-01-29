#include "main.h"


main::main()
{
}


main::~main()
{
}

static const float ROTATE_SPEED = DX_PI_F / 90;//回転スピード
double map(double v, double sx, double sn, double dx, double dn)
{
	return (v - sn) * (dx - dn) / (sx - sn) + dn;
}
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
		Position pos;
		py PY;
		float cameraX = 0, cameraZ = 0;    //カメラの座標
		const float targetX = 0, targetZ = 0;//カメラの視線の先ターゲットの座標
		float x = 0.0, y = 0.0, z = 0.0;
		//3Dモデルの読み込み
		int ModelHandle = MV1LoadModel("./model/bokoboko.pmx");
		//奥行0.1～1000までをカメラの描画範囲とする
		SetCameraNearFar(0.1f, 1000.0f);

		//第一引数の視点から第二引数のターゲットを見る角度にカメラを設置
		SetCameraPositionAndTarget_UpVecY(VGet(cameraX, 5, cameraZ), VGet(cameraX, 5, cameraZ + 10));
		PY.pySerialOpen();
		float ang = 0,ang1=0.0;

		DWORD trueTimeStart,trueTimeEnd;
		DWORD falseTimeStart, falseTimeEnd;
		double trueTimeAve = 0.0, trueTimeSum = 0.0;
		double falseTimeAve = 0.0, falseTimeSum = 0.0;

		bool isOpenFlg = false;
		int trueCount = 0, falseCount = 0;


		while (ProcessMessage() == 0){
			isOpenFlg = false;
			// 画面に描かれているものを一回全部消す
			ClearDrawScreen();
			DWORD start = timeGetTime();       // スタート時間
			
			CV.readCapture(false);
			DX.setBaseImage(CV.getImageData());
			DX.createGraphHandle();


			// フレームの内容を画面に描画
			DrawGraph(0, 0, DX.getCVImage(), FALSE);

			pos = CV.getPosition(false);
			DX.setBaseImage(CV.getImageData());
			DX.createGraphHandle();


			// フレームの内容を画面に描画
			DrawGraph(0, 0, DX.getCVImage(), FALSE);
			
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
			//上下±10.0,左右±15.0
			//MV1SetPosition(ModelHandle, VGet(pos.fx, -pos.fy, 20.0f));
			int isOpen = PY.pySerialIsOpen();
			if (isOpen){
				isOpenFlg = true;
				int befAng[2] = { ang, ang1 };
			
				int *rot = PY.pySerialRead(befAng);

				DrawFormatString(0, 120, GetColor(255, 255, 255), "serialRead = %d,%d", rot[0], rot[1]);

					ang = rot[0] * DX_PI_F / 180.0f;
					ang1 = rot[1] * DX_PI_F / 180.0f;
					if (ang == 0.0 && ang1 == 0.0){
						ang = ang;
					}
			}
			else{
				ang = 0.0;
				ang1 = 0.0;
			}
			MV1SetPosition(ModelHandle, VGet(pos.fx, -pos.fy+5.0, 20.0f));
			MV1SetRotationXYZ(ModelHandle, VGet(-ang, 0.0, -ang1));

			// ３Ｄモデルの描画
			MV1DrawModel(ModelHandle);
			
			//経過時間
			DWORD end = timeGetTime();    // 終了時間
			double time = (double)(end - start) / 1000;

			if (isOpenFlg){
				trueTimeSum+=time;
				trueCount++;
				trueTimeAve = trueTimeSum / trueCount;
			}
			else{
				falseTimeSum += time;
				falseCount++;
				falseTimeAve = falseTimeSum / falseCount;
			}

			DrawFormatString(20, 20, GetColor(0, 0, 255), "time = %lf,fps = %lf", time , 1/time);
			DrawFormatString(20, 50, GetColor(0, 0, 255), "x = %lf : y = %lf",pos.fx,pos.fy);
			//pos = DX.getScreenPos(ModelHandle);
			DrawFormatString(20, 70, GetColor(0, 255, 255), "x = %lf : y = %lf", pos.fx, pos.fy);
			DrawFormatString(20, 90, GetColor(255, 255, 0), "angle=%lf", (CV.getAngle()*180.0 / DX_PI));

			DrawFormatString(20, 110, GetColor(0, 0, 255), "true  time = %lf,fps = %lf", trueTimeAve, 1 / trueTimeAve);
			DrawFormatString(20, 130, GetColor(0, 0, 255), "false time = %lf,fps = %lf", falseTimeAve, 1 / falseTimeAve);
			// 裏画面の内容を表画面に反映
			ScreenFlip();
			//ang+=0.05;
			//ang1 += 0.1;
			if (ang > 360){
				//ang = 0;
			}
			if (ang1 > 360){
				//ang1 = 0;
			}
			if (CheckKeyInput(KEY_INPUT_ESCAPE) > 0){
				break;
			}
		}

		CV.cap.release();
		DxLib_End();
		return 0;				// ソフトの終了 
}