#include "DxLib.h"
#include "Input.h"
#include "SceneSelectStage.h"
#include "SceneTitle.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneTitle::SceneTitle()
{
	m_titleLogo = LoadGraph("data/UI/titleLogo.png");
}


/// <summary>
/// デストラクタ
/// </summary>
SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleLogo);
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
/// <param name="input">入力状態</param>
/// <returns></returns>
std::shared_ptr<SceneBase> SceneTitle::Update(Input& input)
{
	// シーン遷移
	if (input.IsTriggered("OK"))
	{
		return std::make_shared<SceneSelectStage>();
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneTitle::Draw()
{
	DrawRectRotaGraph(1000, 400, 0, 0, 1920, 1080, 0.5f, 0.0f, m_titleLogo, true);

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "タイトル画面", 0xffffff);
#endif
}
