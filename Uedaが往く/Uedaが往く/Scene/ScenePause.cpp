#include "DxLib.h"
#include "Input.h"
#include "ScenePause.h"
#include "SceneStage1.h"
#include "SceneSelectStage.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pScene">前に実行していたシーン</param>
ScenePause::ScenePause(std::shared_ptr<SceneBase> pScene)
{
	m_select = Select::kBack;
	m_pPrevScene = pScene;
}


/// <summary>
/// デストラクタ
/// </summary>
ScenePause::~ScenePause()
{
}


/// <summary>
/// 初期化
/// </summary>
void ScenePause::Init()
{
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力状態</param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> ScenePause::Update(Input& input)
{
	if (input.IsTriggered("OK"))
	{
		if (m_select == Select::kBack)
		{
			return m_pPrevScene;
		}
		else if (m_select == Select::kRetry)
		{
			return std::make_shared<SceneStage1>();
		}
		else if (m_select == Select::kStageSelect)
		{
			return std::make_shared<SceneSelectStage>();
		}
	}

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void ScenePause::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	m_pPrevScene->Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "ポーズ画面", 0xffffff);
#endif
}
