#include "DxLib.h"
#include "ScenePlaying.h"
#include "SceneClear.h"
#include "SceneTitle.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "Light.h"
#include "Confetti.h"
#include "Font.h"
#include "Sound.h"
#include "Input.h"

// 定数
namespace
{	
	/*フェード*/
	constexpr int kFadeFrame = 8;			// フェード変化量
	constexpr int kStartFadeAlpha = 200;	// スタート時のフェードα値
	constexpr int kMaxFadeAlpha = 255;		// 最大フェードα値

	/*操作説明画面*/
	constexpr int kOperationFramePosX = 40;			// 枠表示位置X
	constexpr int kOperationFramePosY = 340;		// 枠表示位置Y
	constexpr int kOperationWidth = 200;			// 枠の横幅
	constexpr int kOperationHeight = 770;			// 枠の縦幅
	constexpr int kOperationBackColor = 0x000000;	// 枠の背景色

	// テキスト
	constexpr int kTaskPosX = 40;				// タスク表示位置X
	constexpr int kTaskPosY = 50;				// タスク表示位置Y
	constexpr int kTaskColor = 0xffffff;		// タスクの文字色
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
	constexpr float kHalf = 0.5f;			// 半分
	// テキスト
	constexpr int kTextColor = 0x000000;	// テキストの色
	constexpr int kBackPosX = 830;			// "ゲームに戻る"表示位置X
	constexpr int kBackPosY = 340;			// "ゲームに戻る"表示位置Y
	constexpr int kRetryPosX = 890;			// "リトライ"表示位置X
	constexpr int kRetryPosY = 540;			// "リトライ"表示位置Y
	constexpr int kTitlePosX = 810;			// "タイトルに戻る"表示位置Y
	constexpr int kTitlePosY = 740;			// "タイトルに戻る"表示位置Y

	/*クリア演出*/
	constexpr float kClearStagingTime = 240.0f;	 // クリア演出の時間
	constexpr float kClearSETime = 180.0f;		 // クリアSEを止める時間
	constexpr float kClearCheersSETime = 200.0f; // 歓声のSEを再生する時間
	constexpr int kAddPal = 200;				 // 加算ブレンドの値

	/*シャドウマップ*/
	constexpr int kShadowMapSize = 1024;							// 作成するシャドウマップのサイズ
	const VECTOR kShadowMapMinPos = VGet(-500.0f, 0.0f, -500.0f);   // シャドウマップの範囲の最小値
	const VECTOR kShadowMapMaxPos = VGet(500.0f, 200.0f, 500.0f);   // シャドウマップの範囲の最大値
}

/// <summary>
/// コンストラクタ
/// </summary>
ScenePlaying::ScenePlaying() :
	m_select(Select::kBack),
	m_isOperation(true),
	m_isPause(false),
	m_frame(0),
	m_frameAnimTime(0.0f),
	m_clearStagingTime(kClearStagingTime)
{
	m_fadeAlpha = kStartFadeAlpha;
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
	StopSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kClearCheersSE)]);
	DeleteGraph(m_frameHandle);
	DeleteGraph(m_pauseBackHandle);
	DeleteGraph(m_padHandle);
	Light::DeleteLight();
	Confetti::DeleteCofetti();
}


/// <summary>
/// 初期化
/// </summary>
void ScenePlaying::Init()
{
	m_pPlayer->Init();
	m_pCamera->Init();
	Light::SetLight();
	Confetti::CreateCofetti();
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力</param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
#ifdef _DEBUG	// デバッグモード
	if (input.IsTriggered("sceneChange"))
	{
		ClearStaging();	// クリア演出を行う
		if (m_clearStagingTime <= 0.0f)
		{
			auto sceneClear = std::make_shared<SceneClear>();
			sceneClear->SetClearTime(m_frame);
			return sceneClear;
		}
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
		FadeOut(); // フェードアウト

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
				FadeIn(); // フェードイン
				PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kSelectSE)], DX_PLAYTYPE_BACK); // SEを鳴らす
				
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

			// プレイヤー更新
			m_pPlayer->Update(input, *m_pCamera, *m_pStage);
			// カメラ更新
			m_pCamera->Update(input, *m_pPlayer, *m_pStage);

			// 表示状態を更新する
			if (!m_pPlayer->GetIsGoal())
			{
				UpdateOperation(input);
				UpdatePause(input);
			}
		}

		// プレイヤーがゴールしたらクリア画面に移動
		if (m_pPlayer->GetIsGoal())
		{
			ClearStaging();	// クリア演出を行う
			if (m_clearStagingTime <= 0.0f)
			{
				auto sceneClear = std::make_shared<SceneClear>();
				sceneClear->SetClearTime(m_frame);
				return sceneClear;
			}
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

	// クリア演出描画
	if (m_pPlayer->GetIsGoal())
	{
		DrawClearStaging();
	}

	// フェードインアウト描画
	DrawFade();

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
/// フェードイン処理
/// </summary>
void ScenePlaying::FadeIn()
{
	m_fadeAlpha += kFadeFrame;
}


/// <summary>
/// フェードアウト処理
/// </summary>
void ScenePlaying::FadeOut()
{
	m_fadeAlpha -= kFadeFrame;
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
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;	// 選択状態を1つ上げる
	}
}


/// <summary>
/// 操作説明の表示状態を更新
/// </summary>
/// <param name="input">入力</param>
void ScenePlaying::UpdateOperation(Input& input)
{
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
}


/// <summary>
/// ポーズ画面の表示状態を更新
/// </summary>
/// <param name="input">入力</param>
void ScenePlaying::UpdatePause(Input& input)
{
	// ボタンを押したらポーズ画面を表示する
	if (input.IsTriggered("pause"))
	{
		// SEを鳴らす
		PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kCursorSE)], DX_PLAYTYPE_BACK);
		m_isPause = true;
	}
}


/// <summary>
/// クリア時の演出	
/// </summary>
void ScenePlaying::ClearStaging()
{
	m_clearStagingTime--;

	Confetti::UpdateCofetti();

	if (m_clearStagingTime >= kClearSETime && !CheckSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kClearSE)]))
	{
		PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kClearSE)], DX_PLAYTYPE_BACK);		  // SEを鳴らす
	}
	else if (m_clearStagingTime <= kClearCheersSETime && !CheckSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kClearCheersSE)]))
	{
		PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kClearCheersSE)], DX_PLAYTYPE_LOOP); // SEを鳴らす
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
		DrawStringToHandle(kOpenClosePosX, kOpenClosePosY, "でとじる",
			0xffffff, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperationMenu)]);
		DrawStringToHandle(kMovePosX, kMovePosY, "移動",
			0xffffff, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperationMenu)]);
		DrawStringToHandle(kJumpPosX, kJumpPosY, "ジャンプ",
			0xffffff, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperationMenu)]);
		DrawStringToHandle(kMoveCameraPosX, kMoveCameraPosY, "カメラ移動",
			0xffffff, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperationMenu)]);
		DrawStringToHandle(kPausePosX, kPausePosY, "ポーズ",
			0xffffff, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperationMenu)]);

		// LSアナログスティック
		DrawRectRotaGraph(kButtonPosX, kButtonPosY + kButtonInterval * Button::kLSButton,
			kButtonSize * Button::kLSButton, 0,
			kButtonSize, kButtonSize, kButtonScale, 0.0f,
			m_padHandle, true);
		// Aボタン
		DrawRectRotaGraph(kButtonPosX, kButtonPosY + kButtonInterval * Button::kAButton,
			kButtonSize * Button::kAButton, 0,
			kButtonSize, kButtonSize, kButtonScale, 0.0f,
			m_padHandle, true);
		// LB,RBボタン
		DrawRectRotaGraph(kLRButtonPosX, kButtonPosY + kButtonInterval * Button::kLRButton,
			kButtonSize * (Button::kLRButton), 0,
			kButtonSize * 2, kButtonSize, kButtonScale, 0.0f,
			m_padHandle, true);
		// 三本線ボタン
		DrawRectRotaGraph(kButtonPosX, kButtonPosY + kButtonInterval * Button::kLineButton,
			kButtonSize * (Button::kLineButton + 1), 0,
			kButtonSize, kButtonSize, kButtonScale, 0.0f,
			m_padHandle, true);
	}
	// 閉じているとき
	else
	{
		DrawStringToHandle(kOpenClosePosX, kOpenClosePosY, "でひらく",
			0xffffff, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperationMenu)]);
	}

	DrawStringToHandle(kOperationPosX, kOperationPosY, "操作説明",
		kOperationColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);

	// ビューボタン
	DrawRectRotaGraph(kViewButtonPosX, kViewButtonPosY,
		kButtonSize * (Button::kViewButton + 1), 0,
		kButtonSize, kButtonSize, kViewButtonScale, 0.0f, m_padHandle, true);

	// 文字表示
	DrawStringToHandle(kTaskPosX, kTaskPosY, "ジャンプですばやく\nゴールをめざせ！\n",
		kTaskColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kTask)]);
}


/// <summary>
/// ポーズ画面を表示
/// </summary>
void ScenePlaying::DrawPause()
{
	// ポーズ画面を表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, kPauseAlpha);
	DrawBox(kPauseBackPosX, kPauseBackPosY, kPauseBackPosX + kPauseWidth, kPauseBackPosY + kPauseHeight, kPauseColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, kMaxFadeAlpha);
	DrawGraph(kPauseFramePosX, kPauseFramePosY, m_pauseBackHandle, true);

	// 枠表示
	for (int i = 0; i < kSelectNum; i++)
	{
		if (m_select == i)
		{
			// 枠のサイズを1.0～1.1で変化させる
			float scale = kFrameScale + kFrameChange * sin(m_frameAnimTime);

			int width, height;
			int size = GetGraphSize(m_frameHandle, &width, &height);
			int scaleWidth = static_cast<int>(width * scale);
			int scaleHeight = static_cast<int>(height * scale);

			// 選択中のボタンを拡大縮小させる
			DrawExtendGraph(
				kFramePosX - static_cast<int>((scaleWidth - width) * kHalf),
				kFramePosY + kSelectMove * i - static_cast<int>((scaleHeight - height) * kHalf),
				kFramePosX + static_cast<int>((scaleWidth - width) * kHalf) + width,
				kFramePosY + static_cast<int>(kSelectMove * i + (scaleHeight - height) * kHalf) + height,
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


/// <summary>
/// クリア時の演出描画
/// </summary>
void ScenePlaying::DrawClearStaging()
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, kAddPal);
	Confetti::DrawCofetti();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, kMaxFadeAlpha);
}
