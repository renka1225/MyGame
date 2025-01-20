#include "DxLib.h"
#include "Game.h"
#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Font.h"
#include "Sound.h"
#include "Input.h"

// 定数
namespace
{
	/*フェード*/
	constexpr int kFadeFrame = 8;			// フェード変化量
	constexpr int kStartFadeAlpha = 200;	// スタート時のフェードα値

	/*UI表示*/
	constexpr int kTitleLogoPosX = 510;		// タイトルロゴ位置X
	constexpr int kTitleLogoPosY = 130;		// タイトルロゴ位置Y
	constexpr int kFramePosX = 1250;		// 枠表示位置X
	constexpr int kFramePosY = 550;			// 枠表示位置Y
	constexpr int kSelectMove = 200;		// 選択表示の移動量
	constexpr float kFrameAnim = 0.05f;		// 枠の拡大縮小アニメーション再生時間
	constexpr float kFrameScale = 1.0f;		// 元の枠のサイズ
	constexpr float kFrameChange = 0.1f;	// 枠のサイズの変化量
	
	/*テキスト*/
	constexpr int kTextColor = 0x000000;	// テキストの色
	constexpr int kStartPosX = 1320;		// "はじめる"表示位置X
	constexpr int kStartPosY = 580;			// "はじめる"表示位置Y
	constexpr int kEndPosX = 1350;			// "おわる"表示位置X
	constexpr int kEndPosY = 780;			// "おわる"表示位置Y

	/*ステージモデル*/
	constexpr float kScale = 0.013f;						// 拡大率
	constexpr float kRotate = 1.0f;							// 3Dモデルの回転量
	const VECTOR kStagePos = VGet(-70.0f, -25.0f, -5.0f);	// 初期位置
	constexpr int kBgColor = 0x2d6676;						// 背景色

	/*カメラ*/
	const VECTOR kCameraPos = VGet(0.0f, 70.0f, -200.0f);	// カメラ位置
	const VECTOR kCameraTarget = VGet(0.0f, 40.0f, 100.0f);	// カメラの視線方向
}

/// <summary>
/// コンストラクタ
/// </summary>
SceneTitle::SceneTitle() :
	m_select(Select::kStart),
	m_stageRotate(0.0f),
	m_frameAnimTime(0.0f),
	m_stageHandle(-1)
{
	m_fadeAlpha = kStartFadeAlpha;
	m_titleHandle = LoadGraph("data/UI/titleLogo.png");
	m_frameHandle = LoadGraph("data/UI/frame.png");
	m_stageHandle = MV1LoadModel("data/Model/stage.mv1");
}


/// <summary>
/// デストラクタ
/// </summary>
SceneTitle::~SceneTitle()
{
	StopSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kTitleBGM)]);
	DeleteGraph(m_titleHandle);
	DeleteGraph(m_frameHandle);
	DeleteGraph(m_stageHandle);
}


/// <summary>
/// 初期化
/// </summary>
void SceneTitle::Init()
{
	// ステージモデルの調整
	MV1SetPosition(m_stageHandle, kStagePos);
	MV1SetScale(m_stageHandle, VGet(kScale, kScale, kScale));
	m_stageRotate = 0.0f;

	// カメラ位置設定
	SetCameraPositionAndTarget_UpVecY(kCameraPos, kCameraTarget);
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力</param>
/// <returns>遷移先のクラス</returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	FadeOut(); 	// フェードアウト

	// BGMを鳴らす
	if (!CheckSoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kTitleBGM)]))
	{
		PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kTitleBGM)], DX_PLAYTYPE_LOOP);
	}

	// ステージを回転させる
	m_stageRotate += kRotate;
	MV1SetRotationXYZ(m_stageHandle, VGet(0.0f, m_stageRotate * -DX_PI_F / 360.0f, 0.0f));

	m_frameAnimTime += kFrameAnim;

	UpdateSelect(input); // 選択状態を更新

	// シーン切り替え
	if (input.IsTriggered("OK"))
	{
		FadeIn();	// フェードイン
		PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kSelectSE)], DX_PLAYTYPE_BACK); // SEを鳴らす

		if (m_select == Select::kStart)
		{
			return std::make_shared<ScenePlaying>(); // ゲームシーンに移動
		}
		else if (m_select == Select::kEnd)
		{
			DxLib_End(); // ゲーム終了
		}
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneTitle::Draw()
{
	// 背景表示
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kBgColor, true);

	// ステージ表示
	MV1DrawModel(m_stageHandle);

	// タイトル表示
	DrawGraph(kTitleLogoPosX, kTitleLogoPosY, m_titleHandle, true);

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
	DrawStringToHandle(kStartPosX, kStartPosY, "はじめる",
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kTitleMenu)]);
	DrawStringToHandle(kEndPosX, kEndPosY, "おわる",
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kTitleMenu)]);

	// フェードインアウト
	DrawFade();

#ifdef _DEBUG
	// デバッグ表示
	DrawFormatString(0, 0, 0xffffff, "タイトル画面");
	// 中心線
	//DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0xffffff);
#endif
}


/// <summary>
/// フェードイン処理
/// </summary>
void SceneTitle::FadeIn()
{
	m_fadeAlpha += kFadeFrame;
}

/// <summary>
/// フェードアウト処理
/// </summary>
void SceneTitle::FadeOut()
{
	m_fadeAlpha -= kFadeFrame;
}


/// <summary>
/// 選択状態を更新する
/// </summary>
/// <param name="input">入力状態</param>
void SceneTitle::UpdateSelect(Input& input)
{
	if (input.IsTriggered("down"))
	{
		m_select = (m_select + 1) % kSelectNum;	// 選択状態を1つ下げる
		PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kCursorSE)], DX_PLAYTYPE_BACK);	// SEを鳴らす
	}
	if (input.IsTriggered("up"))
	{
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;	// 選択状態を1つ上げる
		PlaySoundMem(Sound::m_soundHandle[static_cast<int>(Sound::SoundKind::kCursorSE)], DX_PLAYTYPE_BACK);	// SEを鳴らす
	}
}
