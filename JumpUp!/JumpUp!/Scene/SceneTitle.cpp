#include "DxLib.h"
#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Input.h"

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
		m_select = (m_select - 1) % kSelectNum;	// 選択状態を1つ上げる
	}
}
