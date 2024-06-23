#include "DxLib.h"
#include "SceneClear.h"
#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Font.h"
#include "Game.h"
#include "Input.h"

// 定数
namespace
{
	// UI表示関連
	constexpr int kClearPosX = 510;			// クリア位置X
	constexpr int kClearPosY = 130;			// クリア位置Y
	constexpr int kSelectMove = 200;		// 選択表示の移動量
	constexpr int kFramePosX = 1250;		// 枠表示位置X
	constexpr int kFramePosY = 550;			// 枠表示位置Y
	constexpr float kFrameAnim = 0.05f;		// 枠の拡大縮小アニメーション再生時間
	constexpr float kFrameScale = 1.0f;		// 元の枠のサイズ
	constexpr float kFrameChange = 0.1f;	// 枠のサイズの変化量

	// テキスト関連
	constexpr int kTextColor = 0x000000;	// テキストの色
	constexpr int kStartPosX = 1350;		// もう1回プレイ位置X
	constexpr int kStartPosY = 590;			// もう1回プレイ位置Y
	constexpr int kTitlePosX = 1350;		// タイトルに戻る表示位置X
	constexpr int kTitlePosY = 780;			// タイトルに戻る表示位置Y
}

/// <summary>
/// コンストラクタ
/// </summary>
SceneClear::SceneClear():
	m_select(Select::kStart),
	m_frameAnimTime(0.0f)
{
	m_clearHandle = LoadGraph("data/UI/clear.png");
	m_frameHandle = LoadGraph("data/UI/frame.png");
}


/// <summary>
/// デストラクタ
/// </summary>
SceneClear::~SceneClear()
{
	DeleteGraph(m_clearHandle);
	DeleteGraph(m_frameHandle);
}


/// <summary>
/// 初期化
/// </summary>
void SceneClear::Init()
{
	// 処理なし
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力</param>
/// <returns>遷移先のシーン</returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	m_frameAnimTime += kFrameAnim;

	// 選択状態を更新
	UpdateSelect(input);

	// シーン切り替え
	if (input.IsTriggered("OK"))
	{
		if (m_select == Select::kStart)
		{
			return std::make_shared<ScenePlaying>(); // ゲームシーンに移動
		}
		else if (m_select == Select::kTitle)
		{
			return std::make_shared<SceneTitle>();	// タイトル画面に移動
		}
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneClear::Draw()
{
	// 背景表示
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x2d6676, true);

	// クリアの文字表示
	DrawGraph(kClearPosX, kClearPosY, m_clearHandle, true);

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
	DrawFormatStringToHandle(kStartPosX, kStartPosY,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kClearMenu)], "もう1回プレイ");
	DrawFormatStringToHandle(kTitlePosX, kTitlePosY,
		kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kClearMenu)], "タイトルにもどる");

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "クリア画面", 0xffffff);
#endif
}


/// <summary>
/// 選択状態を更新
/// </summary>
/// <param name="input">入力</param>
void SceneClear::UpdateSelect(Input& input)
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
