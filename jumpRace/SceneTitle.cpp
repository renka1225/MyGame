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
/// <param name="input">ボタン入力</param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	if (input.IsTriggered("sceneChange"))
	{
		return std::make_shared<ScenePlaying>();
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
