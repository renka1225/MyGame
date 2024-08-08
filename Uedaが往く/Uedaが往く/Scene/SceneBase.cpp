#include "DxLib.h"
#include "Input.h"
#include "Game.h"
#include "SceneBase.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneBase::SceneBase():
	m_select(0)
{
	m_cursorHandle = LoadGraph("data/UI/cursor.png");
}


/// <summary>
/// デストラクタ
/// </summary>
SceneBase::~SceneBase()
{
	DeleteGraph(m_cursorHandle);
}


/// <summary>
/// 選択状態を更新
/// </summary>
/// <param name="input">入力状態</param>
/// <param name="selectNum">選択肢の数</param>
void SceneBase::UpdateSelect(Input& input, int selectNum)
{
	if (input.IsTriggered("down"))
	{
		m_select = (m_select + 1) % selectNum;	// 選択状態を1つ下げる
	}
	if (input.IsTriggered("up"))
	{
		m_select = (m_select + (selectNum - 1)) % selectNum;	// 選択状態を1つ上げる
	}
}