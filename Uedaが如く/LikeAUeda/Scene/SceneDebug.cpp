#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneStage1.h"
#include "SceneDebug.h"
#include "Input.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneDebug::SceneDebug():
	m_select(Select::kTitle)
{
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力状態</param>
/// <returns></returns>
std::shared_ptr<SceneBase> SceneDebug::Update(Input& input)
{
	UpdateSelect(input);

	// 遷移
	if (input.IsTriggered("debug_enter"))
	{
		if (m_select == Select::kTitle)
		{
			return std::make_shared<SceneTitle>();
		}
		else if (m_select == Select::kStageSelect)
		{
			//return std::make_shared<SceneSelect>();
		}
		else if (m_select == Select::kOption)
		{
			//return std::make_shared<SceneOption>();
		}
		else if (m_select == Select::kStage1)
		{
			return std::make_shared<SceneStage1>();
		}
		else if (m_select == Select::kStage2)
		{
			//return std::make_shared<SceneStage2>();
		}
	}

	return shared_from_this();
}

/// <summary>
/// 描画
/// </summary>
void SceneDebug::Draw()
{
	DrawString(0, 20, "タイトル", 0xffffff);
	DrawString(0, 40, "ステージ選択", 0xffffff);
	DrawString(0, 60, "オプション", 0xffffff);
	DrawString(0, 80, "ステージ1", 0xffffff);
	DrawString(0, 100, "ステージ2", 0xffffff);
}


/// <summary>
/// 選択状態更新
/// </summary>
/// <param name="input">入力状態</param>
void SceneDebug::UpdateSelect(Input& input)
{
	if (input.IsTriggered("down"))
	{
		m_select = (m_select + 1) % kSelectNum;	// 選択状態を1つ下げる
	}
	if (input.IsTriggered("up"))
	{
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;	// 選択状態を1つ上げる
	}
}
