#include "SceneClear.h"
#include "SceneTitle.h"
#include "Input.h"
#include "DxLib.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneClear::SceneClear()
{
}


/// <summary>
/// デストラクタ
/// </summary>
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
/// <param name="input">ボタン入力</param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> SceneClear::Update(Input& input)
{
	if (input.IsTriggered("sceneChange"))
	{
		return std::make_shared<SceneTitle>();
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneClear::Draw()
{
#ifdef _DEBUG
	// デバッグ表示
	DrawFormatString(0, 0, 0xffffff, "クリア画面");
#endif
}
