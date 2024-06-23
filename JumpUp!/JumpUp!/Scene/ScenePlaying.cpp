#include "DxLib.h"
#include "ScenePlaying.h"
#include "SceneClear.h"
#include "SceneTitle.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "Input.h"

// 定数
namespace
{
	// ポーズ画面
	constexpr int kPausePosX = 600;		// 表示位置X
	constexpr int kPausePosY = 100;		// 表示位置Y
	constexpr int kPauseWidth = 800;	// 横幅
	constexpr int kPauseHeight = 400;	// 縦幅
}

/// <summary>
/// コンストラクタ
/// </summary>
ScenePlaying::ScenePlaying():
	m_select(Select::kBack),
	m_isPause(false)
{
	m_pPlayer = std::make_shared<Player>();
	m_pCamera = std::make_shared<Camera>();
	m_pStage = std::make_shared<Stage>();
}


/// <summary>
/// デストラクタ
/// </summary>
ScenePlaying::~ScenePlaying()
{
	// 処理なし
}


/// <summary>
/// 初期化
/// </summary>
void ScenePlaying::Init()
{
	m_pPlayer->Init();
	m_pCamera->Init();
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力</param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
#ifdef _DEBUG	// デバッグモード
	if (input.IsPressing("sceneChange"))
	{
		return std::make_shared<SceneClear>();	// クリア画面に移動
	}
	// Pキーでポーズ、ポーズ中にPでコマ送り
	if (m_debugState == DebugState::Normal && input.IsPressing("debug_pause"))
	{
		m_debugState = DebugState::Pause;
	}
	if (m_debugState == DebugState::Pause && input.IsPressing("debug_enter"))
	{
		m_debugState = DebugState::Normal;
	}
	if (m_debugState != DebugState::Pause || input.IsPressing("debug_pause"))
#endif
	{
		// ボタンを押したらポーズ画面を開く
		if (m_isPause)
		{
			// 選択状態を更新
			UpdateSelect(input);

			// シーン切り替え
			if (input.IsTriggered("OK"))
			{
				if (m_select == Select::kBack)
				{
					m_isPause = false;
				}
				else if (m_select == Select::kRetry)
				{
					return std::make_shared<ScenePlaying>(); // リトライする
				}
				else if (m_select == Select::kTitle)
				{
					return std::make_shared<SceneTitle>();	// タイトル画面に移動
				}
			}

			// ポーズ画面を閉じる
			if (input.IsTriggered("pause"))
			{
				m_isPause = false;
			}
		}
		else
		{
			// ポーズ画面を表示
			if (input.IsPressing("pause"))
			{
				m_isPause = true;
			}

			// プレイヤー更新
			m_pPlayer->Update(input, *m_pCamera, *m_pStage);

			// カメラ更新
			m_pCamera->Update(input, *m_pPlayer, *m_pStage);
		}

		// プレイヤーがゴールしたらクリア画面に移動
		if (m_pPlayer->GetIsGoal())
		{
			return std::make_shared<SceneClear>();
		}
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void ScenePlaying::Draw()
{
	// ステージ描画
	m_pStage->Draw();

	// プレイヤー描画
	m_pPlayer->Draw(m_pDrawDebug);

	// ポーズ画面表示
	if (m_isPause)
	{
		DrawPause();
	}

#ifdef _DEBUG	// デバッグ表示
	// グリッド表示
	//m_pDrawDebug.DrawGrid();
	// 現在のシーン
	DrawString(0, 0, "プレイ画面", 0xffffff);
#endif
}


/// <summary>
/// 選択状態を更新
/// </summary>
/// <param name="input">入力</param>
void ScenePlaying::UpdateSelect(Input& input)
{
	if (input.IsTriggered("down"))
	{
		m_select = (m_select + 1) % kSelectNum;	// 選択状態を1つ下げる
	}
	if (input.IsTriggered("up"))
	{
		m_select = (m_select - 1) % kSelectNum;	// 選択状態を1つ上げる
	}
}

/// <summary>
/// ポーズ画面を表示
/// </summary>
void ScenePlaying::DrawPause()
{
	// ポーズ画面を表示
	DrawBox(kPausePosX, kPausePosY, kPausePosX + kPauseWidth, kPausePosX + kPauseHeight, 0xff00000, true);

#ifdef _DEBUG
	DrawString(0, 10, "ポーズ中", 0xffffff);
#endif // _DEBUG
}
