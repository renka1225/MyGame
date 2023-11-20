#include "DxLib.h"
#include "Game.h"
#include "SceneManager.h"

// ショットの数
#define SHOT	3

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 一部の関数はDxLib_Init()の前に実行する必要がある
	ChangeWindowMode(true);

	// 画面サイズの変更
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);

	int shotX[SHOT], shotY[SHOT]; // 弾の位置
	int shotFlag[SHOT];				// 弾が存在するか
	int m_shotHandle = LoadGraph("data/image/shotBuster.png"); // 弾の画像

	// 弾が画面上に存在しているか保持する変数に『存在していない』を意味するfalseを代入しておく
	for (int i = 0; i < SHOT; i++)
	{
		shotFlag[i] = false;
	}
	// ショットボタンが前のフレームで押されたかどうかを保存する変数にfalse(押されいない)を代入
	bool prevShotFlag = false;

	// Sceneの開始
	SceneManager* pScene = new SceneManager;
	pScene->Init();

	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		// ゲームの処理
 		pScene->Update();

		// 弾発射
		if (KEY_INPUT_0)
		{
			// 前フレームでショットボタンを押したかが保存されている変数がfalseだったら弾を発射
			if (prevShotFlag == false)
			{
				for (int i = 0; i < 3; i++)
				{
					// 弾iが画面上にでていない場合はその弾を画面に出す
					if (shotFlag[i] == false)
					{
						// 弾iの位置をセット、位置はプレイヤーの中心にする
						shotX[i] = 32;
						shotY[i] = 32;

						// 弾iは現時点を持って存在するので、存在状態を保持する変数に１を代入する
						shotFlag[i] = true;

						break;
					}
				}
			}
			else
			{
				// ショットボタンが押されていなかった場合は
				// 前フレームでショットボタンが押されていたかを保存する変数にfalse(おされていない)を代入
				prevShotFlag = false;
			}
		}

		for (int i = 0; i < SHOT; i++)
		{
			if (shotFlag[i] == true)
			{
				// 弾iを１６ドット上に移動させる
				shotY[i] -= 8;

				// 画面外に出てしまった場合は存在状態を保持している変数にfalse(存在しない)を代入する
				if (shotY[i] < -80)
				{
					shotFlag[i] = false;
				}

				DrawGraph(shotX[i], shotY[i], m_shotHandle, FALSE);
			}
		}

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
	pScene->End();

	// メモリの解放
	delete pScene;
	pScene = nullptr;

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}