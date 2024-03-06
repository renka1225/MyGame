#include "SceneGameover.h"
#include "SceneTitle.h"
#include "Input.h"
#include "DxLib.h"

SceneGameover::SceneGameover()
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
}


/// <summary>
/// 終了
/// </summary>
void SceneGameover::End()
{
}
