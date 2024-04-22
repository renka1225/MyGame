#include "ScenePlaying.h"
#include "SceneClear.h"
#include "Input.h"
#include "DxLib.h"

/// <summary>
/// コンストラクタ
/// </summary>
ScenePlaying::ScenePlaying()
{
}


/// <summary>
/// 初期化
/// </summary>
void ScenePlaying::Init()
{
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">ボタン入力</param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
	if (input.IsTriggered("OK"))
	{
		return std::make_shared<SceneClear>();
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void ScenePlaying::Draw()
{
#ifdef _DEBUG
	// MEMO:デバッグ表示
	DrawFormatString(0, 0, 0xffffff, "プレイ画面");
#endif
}
