#include "DxLib.h"
#include "Input.h"
#include "SceneOption.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneOption::SceneOption(std::shared_ptr<SceneBase> pScene):
	m_pPrevScene(pScene)
{
}


/// <summary>
/// デストラクタ
/// </summary>
SceneOption::~SceneOption()
{
}


/// <summary>
/// 初期化
/// </summary>
void SceneOption::Init()
{
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input"></param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> SceneOption::Update(Input& input)
{
	if (input.IsTriggered("back"))
	{
		return m_pPrevScene;	// 前の画面にもどる
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneOption::Draw()
{
	// 選択項目表示
	DrawString(200, 300, "サウンド", 0xffffff);
	DrawString(200, 500, "明るさ", 0xffffff);
	DrawString(200, 700, "ボタン配置", 0xffffff);

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "オプション画面", 0xffffff);
#endif
}
