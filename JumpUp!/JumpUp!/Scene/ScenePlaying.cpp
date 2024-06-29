#include "DxLib.h"
#include "ScenePlaying.h"
#include "SceneClear.h"
#include "SceneTitle.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "Font.h"
#include "Sound.h"
#include "Input.h"

// 定数
namespace
{	
	/*操作説明画面*/
	constexpr int kOperationFramePosX = 40;			// 枠表示位置X
	constexpr int kOperationFramePosY = 300;		// 枠表示位置Y
	constexpr int kOperationWidth = 200;			// 枠の横幅
	constexpr int kOperationHeight = 780;			// 枠の縦幅
	constexpr int kOperationBackColor = 0x000000;	// 枠の背景色
	// テキスト
	constexpr int kOpenClosePosX = 90;			// "ひらく、とじる"表示位置X
	constexpr int kOpenClosePosY = 390;			// "ひらく、とじる"表示位置Y
	constexpr int kOperationPosX = 50;			// "操作説明"表示位置X
	constexpr int kOperationPosY = 350;			// "操作説明"表示位置Y
	constexpr int kMovePosX = 50;				// "移動"表示位置X
	constexpr int kMovePosY = 450;				// "移動"表示位置Y
	constexpr int kJumpPosX = 50;				// "ジャンプ"表示位置X
	constexpr int kJumpPosY = 530;				// "ジャンプ"表示位置Y
	constexpr int kMoveCameraPosX = 50;			// "カメラ移動"表示位置X
	constexpr int kMoveCameraPosY = 610;		// "カメラ移動"表示位置Y
	constexpr int kPausePosX = 50;				// "ポーズ"表示位置X
	constexpr int kPausePosY = 690;				// "ポーズ"表示位置Y
	constexpr int kOperationColor = 0x34a3f8;	// "操作説明"の文字色
	// ボタン画像
	constexpr int kButtonSize = 32;				// ボタン1つのサイズ
	constexpr float kButtonScale = 1.3f;		// ボタンの拡大率
	constexpr int kButtonPosX = 110;			// ボタンの表示位置X
	constexpr int kButtonPosY = 500;			// ボタンの表示位置Y
	constexpr int kLRButtonPosX = 120;			// LB,RBボタンの表示位置X
	constexpr int kViewButtonPosX = 70;			// ビューボタンの表示位置X
	constexpr int kViewButtonPosY = 400;		// ビューボタンの表示位置Y
	constexpr float kViewButtonScale = 1.0f;	// ビューボタンの拡大率
	constexpr int kButtonInterval = 80;			// ボタンの表示間隔

	/*ポーズ画面*/
	constexpr int kPauseFramePosX = 650;	// 枠表示位置X
	constexpr int kPauseFramePosY = 200;	// 枠表示位置Y
	constexpr int kPauseBackPosX = 670;		// 背景表示位置X
	constexpr int kPauseBackPosY = 210;		// 背景表示位置Y
	constexpr int kPauseWidth = 620;		// 背景の横幅
	constexpr int kPauseHeight = 700;		// 背景の縦幅
	constexpr int kPauseColor = 0x040a15;	// ポーズ画面の背景色
	constexpr int kPauseAlpha = 180;		// ポーズ画面のα値
	// 枠
	constexpr int kFramePosX = 780;			// 枠表示位置X
	constexpr int kFramePosY = 300;			// 枠表示位置Y
	constexpr int kSelectMove = 200;		// 選択表示の移動量
	constexpr float kFrameAnim = 0.05f;		// 枠の拡大縮小アニメーション再生時間
	constexpr float kFrameScale = 1.0f;		// 元の枠のサイズ
	constexpr float kFrameChange = 0.1f;	// 枠のサイズの変化量
	// テキスト
	constexpr int kTextColor = 0x000000;	// テキストの色
	constexpr int kBackPosX = 830;			// "ゲームに戻る"表示位置X
	constexpr int kBackPosY = 340;			// "ゲームに戻る"表示位置Y
	constexpr int kRetryPosX = 890;			// "リトライ"表示位置X
	constexpr int kRetryPosY = 540;			// "リトライ"表示位置Y
	constexpr int kTitlePosX = 810;			// "タイトルに戻る"表示位置Y
	constexpr int kTitlePosY = 740;			// "タイトルに戻る"表示位置Y
}

/// <summary>
/// コンストラクタ
/// </summary>
ScenePlaying::ScenePlaying():
	m_select(Select::kBack),
	m_isOperation(true),
	m_isPause(false),
	m_frame(0),
	m_frameAnimTime(0.0f)
{
	m_pPlayer = std::make_shared<Player>();
	m_pCamera = std::make_shared<Camera>();
	m_pStage = std::make_shared<Stage>();

	m_frameHandle = LoadGraph("data/UI/frame.png");
	m_pauseBackHandle = LoadGraph("data/UI/pauseBack.png");
	m_padHandle = LoadGraph("data/UI/pad.png");
}


/// <summary>
/// デストラクタ
/// </summary>
ScenePlaying::~ScenePlaying()
{
	StopSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kPlayBGM)]);
	DeleteGraph(m_frameHandle);
	DeleteGraph(m_pauseBackHandle);
	DeleteGraph(m_padHandle);
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
		auto sceneClear = std::make_shared<SceneClear>();
		sceneClear->SetClearTime(m_frame);
		return sceneClear;	// クリア画面に移動
	}
	// Pキーでポーズ、ポーズ中にPでコマ送り
	if (m_debugState == DebugState::Normal && input.IsTriggered("debug_pause"))
	{
		m_debugState = DebugState::Pause;
	}
	if (m_debugState == DebugState::Pause && input.IsTriggered("debug_enter"))
	{
		m_debugState = DebugState::Normal;
	}
	if (m_debugState != DebugState::Pause || input.IsTriggered("debug_pause"))
#endif
	{
		// BGMを鳴らす
		if (!CheckSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kPlayBGM)]))
		{
			PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kPlayBGM)], DX_PLAYTYPE_LOOP);
		}

		// ボタンを押したらポーズ画面を開く
		if (m_isPause)
		{
			m_frameAnimTime += kFrameAnim;

			// 選択状態を更新
			UpdateSelect(input);

			// シーン切り替え
			if (input.IsTriggered("OK"))
			{
				// SEを鳴らす
				PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kSelectSE)], DX_PLAYTYPE_BACK);
				
				if (m_select == Select::kBack)
				{
					m_isPause = false;	// ゲームに戻る
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
		}
		else
		{
			m_frame++;	// 経過フレーム数を更新

			// 操作説明画面の表示非表示
			if (input.IsTriggered("operation"))
			{
				if (m_isOperation)
				{
					m_isOperation = false;
				}
				else
				{
					m_isOperation = true;
				}
			}

			// ボタンを押したらポーズ画面を表示する
			if (input.IsTriggered("pause"))
			{
				// SEを鳴らす
				PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kCursorSE)], DX_PLAYTYPE_BACK);
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
			auto sceneClear = std::make_shared<SceneClear>();
			sceneClear->SetClearTime(m_frame);

			return sceneClear;
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

	// 操作説明表示
	DrawOperation();

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
	// タイム表示
	m_pDrawDebug.DrawTime(m_frame);
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
		PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kCursorSE)], DX_PLAYTYPE_BACK); //SEを鳴らす
		m_select = (m_select + 1) % kSelectNum;	// 選択状態を1つ下げる
	}
	if (input.IsTriggered("up"))
	{
		PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kCursorSE)], DX_PLAYTYPE_BACK); //SEを鳴らす
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;;	// 選択状態を1つ上げる
	}
}


/// <summary>
/// 操作説明を表示
/// </summary>
void ScenePlaying::DrawOperation()
{
	// 開いているとき
	if (m_isOperation)
	{
		// 背景を薄く表示する
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, kPauseAlpha);
		DrawBox(kOperationFramePosX, kOperationFramePosY, kOperationWidth, kOperationHeight, kOperationBackColor, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		// 文字表示
		DrawFormatStringToHandle(kOpenClosePosX, kOpenClosePosY,
			0xffffff, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperationMenu)], "でとじる");
		DrawFormatStringToHandle(kMovePosX, kMovePosY,
			0xffffff, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperationMenu)], "移動");
		DrawFormatStringToHandle(kJumpPosX, kJumpPosY,
			0xffffff, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperationMenu)], "ジャンプ");
		DrawFormatStringToHandle(kMoveCameraPosX, kMoveCameraPosY,
			0xffffff, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperationMenu)], "カメラ移動");
		DrawFormatStringToHandle(kPausePosX, kPausePosY,
			0xffffff, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperationMenu)], "ポーズ");

		// LSアナログスティック
		DrawRectRotaGraph(kButtonPosX, kButtonPosY + kButtonInterval * Button::kLSButton,
			kButtonSize * Button::kLSButton, 0.0f,
			kButtonSize, kButtonSize, kButtonScale, 0.0f,
			m_padHandle, true);
		// Aボタン
		DrawRectRotaGraph(kButtonPosX, kButtonPosY + kButtonInterval * Button::kAButton,
			kButtonSize * Button::kAButton, 0.0f,
			kButtonSize, kButtonSize, kButtonScale, 0.0f,
			m_padHandle, true);
		// LB,RBボタン
		DrawRectRotaGraph(kLRButtonPosX, kButtonPosY + kButtonInterval * Button::kLRButton,
			kButtonSize * (Button::kLRButton), 0.0f,
			kButtonSize * 2, kButtonSize, kButtonScale, 0.0f,
			m_padHandle, true);
		// 三本線ボタン
		DrawRectRotaGraph(kButtonPosX, kButtonPosY + kButtonInterval * Button::kLineButton,
			kButtonSize * (Button::kLineButton + 1), 0.0f,
			kButtonSize, kButtonSize, kButtonScale, 0.0f,
			m_padHandle, true);
	}
	// 閉じているとき
	else
	{
		DrawFormatStringToHandle(kOpenClosePosX, kOpenClosePosY,
			0xffffff, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperationMenu)], "でひらく");
	}

	DrawFormatStringToHandle(kOperationPosX, kOperationPosY,
		kOperationColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)], "操作説明");

	// ビューボタン
	DrawRectRotaGraph(kViewButtonPosX, kViewButtonPosY,
		kButtonSize * (Button::kViewButton + 1), 0.0f,
		kButtonSize, kButtonSize, kViewButtonScale, 0.0f, m_padHandle, true);
}


/// <summary>
/// ポーズ画面を表示
/// </summary>
void ScenePlaying::DrawPause()
{
	// ポーズ画面を表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kPauseAlpha);
	DrawBox(kPauseBackPosX, kPauseBackPosY, kPauseBackPosX + kPauseWidth, kPauseBackPosY + kPauseHeight, kPauseColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawGraph(kPauseFramePosX, kPauseFramePosY, m_pauseBackHandle, true);

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
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kPauseMenu)], "タイトルにもどる");

#ifdef _DEBUG
	DrawString(0, 10, "ポーズ中", 0xffffff);
#endif
}
