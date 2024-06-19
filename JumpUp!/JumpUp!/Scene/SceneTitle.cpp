#include "DxLib.h"
#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Input.h"

// 定数
namespace
{
	constexpr int kTitleLogoPosX = 350;	// タイトルロゴ位置X
	constexpr int kTitleLogoPosY = 100;	// タイトルロゴ位置Y

	constexpr int kTextColor = 0xffffff; // テキストの色
	constexpr int kStartPosX = 1000;	 // スタート表示位置X
	constexpr int kStartPosY = 700;		 // スタート表示位置Y
	constexpr int kEndPosX = 1000;		 // ゲーム終了表示位置X
	constexpr int kEndPosY = 900;		 // ゲーム終了表示位置Y

	constexpr int kSelectColor = 0xffffff;		// 選択中カーソルの色
	static constexpr int kNowSelectPosX = 900;	// 選択中表示位置X
	static constexpr int kNowSelectPosY = 690;	// 選択中表示位置Y
	static constexpr int kNowSelectWidth = 210;	// 選択中表示の横幅
	static constexpr int kNowSelectHeight = 61;	// 選択中表示の縦幅
	static constexpr int kSelectMove = 80;		// 選択表示の移動量
}

/// <summary>
/// コンストラクタ
/// </summary>
SceneTitle::SceneTitle() :
	m_select(Select::kStart)
{
}


/// <summary>
/// デストラクタ
/// </summary>
SceneTitle::~SceneTitle()
{
}


/// <summary>
/// 初期化
/// </summary>
void SceneTitle::Init()
{
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力</param>
/// <returns>遷移先のクラス</returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
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
#ifdef _DEBUG
	// デバッグ表示
	DrawFormatString(0, 0, 0xffffff, "タイトル画面");
#endif

	// 選択中の項目に色をつける
	int nowSelectPosY = kNowSelectPosY + kSelectMove * m_select;
	DrawBox(kNowSelectPosX, nowSelectPosY, kNowSelectPosX + kNowSelectWidth, nowSelectPosY + kNowSelectHeight,
		kSelectColor, true);

	// 選択項目表示
	DrawString(kStartPosX, kStartPosY, "Start\n", kTextColor);
	DrawString(kEndPosX, kEndPosY, "End\n", kTextColor);
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
	}
	if (input.IsTriggered("up"))
	{
		m_select = (m_select - 1) % 1;	// 選択状態を1つ上げる
	}
}
