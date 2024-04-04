#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Input.h"
#include "ManagerFont.h"
#include "DxLib.h"

SceneTitle::SceneTitle():
	m_textFrame(0)
{
}


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
///	更新
/// </summary>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	m_textFrame++;

#if _DEBUG
	// MEMO:デバック用
	if (input.IsTriggered("debug"))
	{
		return std::make_shared<ScenePlaying>();
	}
#endif

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneTitle::Draw()
{
#if _DEBUG
	// MEMO:デバッグ表示
	DrawFormatString(0, 0, 0xffffff, "タイトル画面");
#endif

	// テキスト表示
	if (m_textFrame % 60 >= 30) return;
	DrawFormatStringToHandle(kTextPosX, kTextPosY, 0xffd700, m_pFont->GetTextFont(), "Press A");
}


/// <summary>
/// 終了処理
/// </summary>
void SceneTitle::End()
{
}
