#include "DxLib.h"
#include "Input.h"
#include "SceneOption.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneOption::SceneOption()
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
/// <returns></returns>
std::shared_ptr<SceneBase> SceneOption::Update(Input& input)
{
	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneOption::Draw()
{
#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "オプション画面", 0xffffff);
#endif
}
