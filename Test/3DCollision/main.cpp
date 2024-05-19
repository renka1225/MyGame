#include "DxLib.h"
#include "Cube.h"
#include "Cube2.h"
#include "Sphere.h"
#include "Sphere2.h"
#include "Capsule.h"
#include "Capsule2.h"
#include "Triangle.h"
#include "Plane.h"
#include <cmath>
#include <memory>

namespace
{
	constexpr float kCameraDist = 96;
	constexpr float kCameraHeight = 32;
}

void DrawGrid()
{
	for (int x = -50; x <= 50; x += 10)
	{
		DrawLine3D(VGet(static_cast<float>(x), 0, -50), VGet(static_cast<float>(x), 0, 50), 0xffff00);
	}
	for (int z = -50; z <= 50; z += 10)
	{
		DrawLine3D(VGet(-50, 0, static_cast<float>(z)), VGet(50, 0, static_cast<float>(z)), 0xff0000);
	}

	// X+-,Z+-の方向が分かりやすいように表示を追加する
	VECTOR dispPos = ConvWorldPosToScreenPos(VGet(50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(-50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X-", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, 50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, -50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z-", 0xffffff);
	}
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// windowモード設定
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetUseBackCulling(true);

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	float cameraAngle = -DX_PI_F / 2;

	// ポインタ
	std::shared_ptr<Plane> pPlane = std::make_shared<Plane>();
	std::shared_ptr<Cube2> pCube2 = std::make_shared<Cube2>();
	std::shared_ptr<Cube> pCube = std::make_shared<Cube>(pPlane, pCube2);
	std::shared_ptr<Sphere2> pSphere2 = std::make_shared<Sphere2>();
	std::shared_ptr<Capsule2> pCapsule2 = std::make_shared<Capsule2>();
	std::shared_ptr<Capsule> pCapsule = std::make_shared<Capsule>(pCapsule2);
	std::shared_ptr<Triangle> pTriangle = std::make_shared<Triangle>();
	std::shared_ptr<Sphere> pSphere = std::make_shared<Sphere>(pSphere2, pCapsule2, pTriangle);

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();

		/*カメラ調整*/
		if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_5))
		{
			cameraAngle += 0.05f;
		}
		if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_6))
		{
			cameraAngle -= 0.05f;
		}

		SetCameraNearFar(1.0f, 180.0f);
		VECTOR cameraPos;
		cameraPos.x = cosf(cameraAngle) * kCameraDist;
		cameraPos.y = kCameraHeight;
		cameraPos.z = sinf(cameraAngle) * kCameraDist;
		SetCameraPositionAndTarget_UpVecY(cameraPos, VGet(0, 0, 0));
		
		/*グリッド表示*/
		DrawGrid();

		/*3Dモデルの更新*/
		pCube->Update();
		//pSphere->Update();
		//pCapsule->Update();
		pPlane->Update();

		/*3Dモデル表示*/
		// 立方体を表示
		pCube->Draw();
		//pCube2->Draw();

		// 球を表示
		//pSphere->Draw();
		//pSphere2->Draw();

		// カプセルを表示
		//pCapsule->Draw();
		//pCapsule2->Draw();

		// 三角形を表示
		//pTriangle->Draw();

		// 平面を表示
		pPlane->Draw();

		//裏画面を表画面を入れ替える
		ScreenFlip();

		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}