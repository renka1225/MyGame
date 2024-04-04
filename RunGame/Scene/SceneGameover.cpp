#include "SceneGameover.h"
#include "SceneTitle.h"
#include "Input.h"
#include "ManagerFont.h"
#include "DxLib.h"

SceneGameover::SceneGameover():
	m_textFrame(0)
{
}


SceneGameover::~SceneGameover()
{
}


/// <summary>
/// 初期化
/// </summary>
void SceneGameover::Init()
{
}


/// <summary>
/// 更新
/// </summary>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> SceneGameover::Update(Input& input)
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
void SceneGameover::Draw()
{
#if _DEBUG
	DrawFormatString(0, 0, 0xffffff, "ゲームオーバー画面");
#endif

	DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffd700, m_pFont->GetTextFont(), "もう1回遊ぶ");
	if (m_textFrame % 60 >= 30) return;
	DrawFormatStringToHandle(kText2PosX, kText2PosY, 0xffd700, m_pFont->GetTextFont(), "タイトルにもどる");
}


/// <summary>
/// 終了
/// </summary>
void SceneGameover::End()
{
}
