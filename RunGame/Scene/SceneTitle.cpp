#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Input.h"
#include "DxLib.h"

SceneTitle::SceneTitle()
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
	DrawFormatString(0, 0, 0xffffff, "タイトル画面");
#endif
}


/// <summary>
/// 終了処理
/// </summary>
void SceneTitle::End()
{
}
