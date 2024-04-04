#include "SceneClear.h"
#include "SceneTitle.h"
#include "Input.h"
#include "ManagerFont.h"
#include "DxLib.h"

SceneClear::SceneClear():
	m_textFrame(0)
{
}


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
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	m_textFrame++;

#if _DEBUG
	// MEMO:デバック用
	if (input.IsTriggered("debug"))
	{
		return std::make_shared<SceneTitle>();
	}
#endif

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneClear::Draw()
{
#if _DEBUG
	DrawFormatString(0, 0, 0xffffff, "クリア画面");
#endif

	DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffd700, m_pFont->GetTextFont(), "タイトルにもどる");
	if (m_textFrame % 60 >= 30) return;
	DrawFormatStringToHandle(kText2PosX, kText2PosY, 0xffd700, m_pFont->GetTextFont(), "もう1回遊ぶ");
}


/// <summary>
/// 終了
/// </summary>
void SceneClear::End()
{
}
