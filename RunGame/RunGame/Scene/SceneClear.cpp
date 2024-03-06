#include "SceneClear.h"
#include "SceneTitle.h"
#include "Input.h"
#include "DxLib.h"

SceneClear::SceneClear()
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
}


/// <summary>
/// 終了
/// </summary>
void SceneClear::End()
{
}
