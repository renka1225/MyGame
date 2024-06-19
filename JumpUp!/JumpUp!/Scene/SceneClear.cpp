#include "DxLib.h"
#include "SceneClear.h"
#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Input.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneClear::SceneClear():
	m_select(Select::kStart)
{
}


/// <summary>
/// デストラクタ
/// </summary>
SceneClear::~SceneClear()
{
}


/// <summary>
/// 初期化
/// </summary>
void SceneClear::Init()
{
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力</param>
/// <returns>遷移先のシーン</returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
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
