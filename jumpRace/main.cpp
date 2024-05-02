#include "DxLib.h"
#include "SceneManager.h"
#include "Input.h"
#include "Game.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("HOPPINGRACE");

	// 画面サイズの変更
	ChangeWindowMode(true);
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	SetUseZBufferFlag(true);	// Zバッファを使用する

	// ライトの調整
	//SetLightDifColor(GetColorF(0.8f, 0.5f, 0.3f, 0.0f));
	//SetLightSpcColor(GetColorF(0.5f, 0.5f, 0.5f, 0.5f));
	SetLightAmbColor(GetColorF(0.8f, 0.0f, 0.0f, 0.0f));

	MATERIALPARAM Material;
	Material.Diffuse = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);	// 拡散光色
	Material.Ambient = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);	// 環境光色
	Material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);	// 反射光色
	Material.Emissive = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);	// 自己発光色
	Material.Power = 20.0f;									// スペキュラの強さ
	SetMaterialParam(Material);

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

		//ChangeLightTypePoint(VGet(0.0f, 500.0f, 200.0f), 1000.0f, 0.0f, 0.0001f, 0.0f);

		// ゲームの処理
		input.Update();
		pScene->Update(input);

		// 描画
		pScene->Draw();

		// 画面が切り替わるのを待つ
		ScreenFlip();

		// escキーでゲーム終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60に固定する
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66ミリ秒(16667マイクロ秒)経過するまで待つ
		}
	}

	DxLib_End();			// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}