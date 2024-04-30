#include "SceneResult.h"
#include "SceneTitle.h"
#include "Input.h"
#include "DxLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneResult::SceneResult()
{
}


/// <summary>
/// デストラクタ
/// </summary>
SceneResult::~SceneResult()
{
}


/// <summary>
/// 初期化
/// </summary>
void SceneResult::Init()
{
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">ボタン入力</param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> SceneResult::Update(Input& input)
{
	if (input.IsTriggered("sceneChange"))
	{
		return std::make_shared<SceneTitle>();		//タイトル画面に移動
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneResult::Draw()
{
#ifdef _DEBUG
	// MEMO:デバッグ表示
	DrawString(0, 0, "結果確認画面", 0xffffff);
#endif

}
