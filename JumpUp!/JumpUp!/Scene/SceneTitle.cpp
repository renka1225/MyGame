#include "DxLib.h"
#include "Game.h"
#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Font.h"
#include "Input.h"

// 定数
namespace
{
	// UI表示関連
	constexpr int kTitleLogoPosX = 510;		// タイトルロゴ位置X
	constexpr int kTitleLogoPosY = 150;		// タイトルロゴ位置Y
	constexpr int kFramePosX = 350;			// 枠表示位置X
	constexpr int kFramePosY = 750;			// 枠表示位置Y
	constexpr int kSelectMove = 700;		// 選択表示の移動量
	
	// テキスト関連
	constexpr int kTextColor = 0x000000;	// テキストの色
	constexpr int kStartPosX = 500;			// スタート表示位置X
	constexpr int kStartPosY = 780;			// スタート表示位置Y
	constexpr int kEndPosX = 1220;			// ゲーム終了表示位置X
	constexpr int kEndPosY = 780;			// ゲーム終了表示位置Y

	// ステージモデル
	constexpr float kScale = 0.1f;							// 拡大率
	constexpr float kRotate = 1.0f;							// 3Dモデルの回転量
	const VECTOR kStagePos = VGet(1000.0f,200.0f, 0.0f);	// 初期位置
}

/// <summary>
/// コンストラクタ
/// </summary>
SceneTitle::SceneTitle() :
	m_select(Select::kStart),
	m_stageRotate(0.0f)
{
	m_titleHandle = LoadGraph("data/UI/titleLogo.png");
	m_frameHandle = LoadGraph("data/UI/frame.png");
	m_selectFrameHandle = LoadGraph("data/UI/selectFrame.png");
	m_stageHandle = MV1LoadModel("data/Model/stage.mv1");
}


/// <summary>
/// デストラクタ
/// </summary>
SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleHandle);
	DeleteGraph(m_frameHandle);
	DeleteGraph(m_selectFrameHandle);
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
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力</param>
/// <returns>遷移先のクラス</returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	// ステージを回転させる
	m_stageRotate += kRotate;
	MV1SetRotationXYZ(m_stageHandle, VGet(0.0f, m_stageRotate * DX_PI_F / 360.0f, 0.0f));

	// 選択状態を更新
	UpdateSelect(input);

	// シーン切り替え
	if (input.IsTriggered("OK"))
	{
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
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x2d6676, true);

	// ステージ表示
	MV1DrawModel(m_stageHandle);

	// タイトル表示
	DrawGraph(kTitleLogoPosX, kTitleLogoPosY, m_titleHandle, true);

	// 枠表示
	for (int i = 0; i < kSelectNum; i++)
	{
		// 選択状態によって枠の画像を変更する
		int frameHandle = -1;
		if (m_select == i)
		{
			frameHandle = m_selectFrameHandle;
		}
		else
		{
			frameHandle = m_frameHandle;
		}
		DrawGraph(kFramePosX + kSelectMove * i, kFramePosY, frameHandle, true);
	}

	// 文字表示
	DrawFormatStringToHandle(kStartPosX, kStartPosY,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::TitleMenu)], "START");
	DrawFormatStringToHandle(kEndPosX, kEndPosY,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::TitleMenu)], "END");

	//DrawString(kStartPosX, kStartPosY, "Start\n", kTextColor);
	//DrawString(kEndPosX, kEndPosY, "End\n", kTextColor);

#ifdef _DEBUG
	// デバッグ表示
	DrawFormatString(0, 0, 0xffffff, "タイトル画面");
	// 中心線
	DrawLine(Game::kScreenWidth * 0.5, 0, Game::kScreenWidth * 0.5, Game::kScreenHeight, 0xfffff);
#endif
}


/// <summary>
/// 選択状態を更新する
/// </summary>
/// <param name="input">入力状態</param>
void SceneTitle::UpdateSelect(Input& input)
{
	if (input.IsTriggered("right"))
	{
		m_select = (m_select + 1) % kSelectNum;	// 選択状態を1つ右にする
	}
	if (input.IsTriggered("left"))
	{
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;	// 選択状態を1つ左にする
	}
}
