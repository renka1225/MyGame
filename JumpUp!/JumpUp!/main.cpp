#include "DxLib.h"
#include "SceneManager.h"
#include "Game.h"
#include "Input.h"
#include "Player.h"
#include <memory>
#include <cmath>

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
	SetMainWindowText("JumpUp!");

	// windowモード設定
	ChangeWindowMode(true);
	// 画面サイズ変更
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// Zバッファの設定
	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetUseBackCulling(true);

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	// SceneManagerを生成
	std::shared_ptr<SceneManager> pScene = std::make_shared<SceneManager>();
	pScene->Init();

	// 入力状態を取得
	Input input;

	// カメラ
	// TODO:後でカメラクラスに移動させる
	float cameraAngle = -DX_PI_F / 2;

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();

		if (input.IsPressing("rotateL"))
		{
			cameraAngle += 0.05f;
		}
		if (input.IsPressing("rotateR"))
		{
			cameraAngle -= 0.05f;
		}

		SetCameraNearFar(1.0f, 180.0f);
		VECTOR cameraPos;
		cameraPos.x = cosf(cameraAngle) * kCameraDist;
		cameraPos.y = kCameraHeight;
		cameraPos.z = sinf(cameraAngle) * kCameraDist;
		SetCameraPositionAndTarget_UpVecY(cameraPos, VGet(0, 0, 0));

		DrawGrid();

		// 更新
		input.Update();
		pScene->Update(input);

		// 描画
		pScene->Draw();

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