#include "SceneTitle.h"
#include "ScenePlaying.h"
#include "Input.h"
#include "DxLib.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneTitle::SceneTitle()
{
}


/// <summary>
/// デストラクタ
/// </summary>
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
/// 更新
/// </summary>
/// <param name="input">入力</param>
/// <returns>遷移先のクラス</returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	if (input.IsTriggered("OK"))
	{
		return std::make_shared<ScenePlaying>(); // ゲームシーンに移動
	}
	else if (input.IsTriggered("debug"))
	{
		DxLib_End(); // ゲーム終了
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneTitle::Draw()
{
#ifdef _DEBUG
	// デバッグ表示
	DrawFormatString(0, 0, 0xffffff, "タイトル画面");
#endif
}
