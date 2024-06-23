#include "DxLib.h"
#include "ScenePlaying.h"
#include "SceneClear.h"
#include "SceneTitle.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "Font.h"
#include "Input.h"

// 定数
namespace
{
	// ポーズ画面
	constexpr int kPausePosX = 600;		// 表示位置X
	constexpr int kPausePosY = 100;		// 表示位置Y
	constexpr int kPauseWidth = 800;	// 横幅
	constexpr int kPauseHeight = 400;	// 縦幅

	// UI表示関連
	constexpr int kSelectMove = 200;		// 選択表示の移動量
	constexpr int kFramePosX = 600;			// 枠表示位置X
	constexpr int kFramePosY = 300;			// 枠表示位置Y
	constexpr float kFrameAnim = 0.05f;		// 枠の拡大縮小アニメーション再生時間
	constexpr float kFrameScale = 1.0f;		// 元の枠のサイズ
	constexpr float kFrameChange = 0.1f;	// 枠のサイズの変化量

	// テキスト関連
	constexpr int kTextColor = 0x000000;	// テキストの色
	constexpr int kBackPosX = 700;			// ゲームに戻る表示位置X
	constexpr int kBackPosY = 590;			// ゲームに戻る表示位置Y
	constexpr int kRetryPosX = 700;			// リトライ表示位置X
	constexpr int kRetryPosY = 780;			// リトライ表示位置Y
	constexpr int kTitlePosX = 700;			// タイトルに戻る表示位置Y
	constexpr int kTitlePosY = 780;			// タイトルに戻る表示位置Y
}

/// <summary>
/// コンストラクタ
/// </summary>
ScenePlaying::ScenePlaying():
	m_select(Select::kBack),
	m_isPause(false),
	m_frameAnimTime(0.0f)
{
	m_pPlayer = std::make_shared<Player>();
	m_pCamera = std::make_shared<Camera>();
	m_pStage = std::make_shared<Stage>();

	m_frameHandle = LoadGraph("data/UI/frame.png");
}


/// <summary>
/// デストラクタ
/// </summary>
ScenePlaying::~ScenePlaying()
{
	DeleteGraph(m_frameHandle);
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
			m_frameAnimTime += kFrameAnim;

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
	SetDrawBlendMode(DX_BLENDMODE_MULA, 200);
	DrawBox(kPausePosX, kPausePosY, kPausePosX + kPauseWidth, kPausePosX + kPauseHeight, 0x0f00dd, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// 枠表示
	for (int i = 0; i < kSelectNum; i++)
	{
		// 選択中のボタンを拡大縮小させる
		if (m_select == i)
		{
			// 枠のサイズを1.0～1.1で変化させる
			float scale = kFrameScale + kFrameChange * sin(m_frameAnimTime);

			int width, height;
			int size = GetGraphSize(m_frameHandle, &width, &height);
			int scaleWidth = static_cast<int>(width * scale);
			int scaleHeight = static_cast<int>(height * scale);

			DrawExtendGraph(
				kFramePosX - static_cast<int>((scaleWidth - width) * 0.5f),
				kFramePosY + kSelectMove * i - static_cast<int>((scaleHeight - height) * 0.5f),
				kFramePosX + static_cast<int>((scaleWidth - width) * 0.5f) + width,
				kFramePosY + static_cast<int>(kSelectMove * i + (scaleHeight - height) * 0.5f) + height,
				m_frameHandle, true);
		}
		else
		{
			DrawGraph(kFramePosX, kFramePosY + kSelectMove * i, m_frameHandle, true);
		}
	}

	// 文字表示
	DrawFormatStringToHandle(kBackPosX, kBackPosY,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kPauseMenu)], "ゲームにもどる");
	DrawFormatStringToHandle(kRetryPosX, kRetryPosY,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kPauseMenu)], "リトライ");
	DrawFormatStringToHandle(kTitlePosX, kTitlePosY,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kPauseMenu)], "リトライ");

#ifdef _DEBUG
	DrawString(0, 10, "ポーズ中", 0xffffff);
#endif // _DEBUG
}
