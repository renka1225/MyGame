#include "DxLib.h"
#include "SceneManager.h"
#include "Input.h"
#include "Game.h"
#include <memory>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("JUMPDUCK");

	ChangeWindowMode(true);

	// 画面サイズの変更
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// SceneManagerを生成
	std::shared_ptr<SceneManager> pScene = std::make_shared<SceneManager>();
	pScene->Init();

	// 入力状態を取得
	Input input;

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// 処理
		input.Update();
		pScene->Update(input);

		// 描画
		pScene->Draw();

		// 画面が切り替わるのを待つ
		ScreenFlip();

		// FPS60に固定する
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66ミリ秒(16667マイクロ秒)経過するまで待つ
		}
	}

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}