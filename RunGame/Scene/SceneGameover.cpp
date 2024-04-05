#include "SceneGameover.h"
#include "SceneTitle.h"
#include "ScenePlaying.h"
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

	//　プレイ画面に遷移
	if (input.IsTriggered("Enter"))
	{
		return std::make_shared<ScenePlaying>();
	}
	// タイトル画面に遷移
	else if (input.IsTriggered("debug"))
	{
		return std::make_shared<SceneTitle>();
	}

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

	if (m_textFrame % 60 >= 30) return;
	DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffd700, m_pFont->GetTextFont(), "もう1回遊ぶ");
	DrawFormatStringToHandle(kText2PosX, kText2PosY, 0xffd700, m_pFont->GetTextFont(), "タイトルにもどる");
}


/// <summary>
/// 終了
/// </summary>
void SceneGameover::End()
{
}
