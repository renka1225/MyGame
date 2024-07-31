#include "DxLib.h"
#include "Input.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "SceneStage1.h"
#include "SceneStage2.h"
#include "SceneTitle.h"
#include "SceneSelectStage.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneSelectStage::SceneSelectStage()
{
	m_select = SelectScene::kStage1;
}


/// <summary>
/// デストラクタ
/// </summary>
SceneSelectStage::~SceneSelectStage()
{
}


/// <summary>
/// 初期化
/// </summary>
void SceneSelectStage::Init()
{
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力処理</param>
/// <returns>遷移先のシーン</returns>
std::shared_ptr<SceneBase> SceneSelectStage::Update(Input& input)
{
	//選択状態更新
	UpdateSelect(input, kSelectNum);

	// シーン遷移
	if (input.IsTriggered("OK"))
	{
		std::shared_ptr<Player> pPlayer = std::make_shared<Player>();
		std::shared_ptr<Camera> pCamera = std::make_shared<Camera>();
		std::shared_ptr<Stage> pStage = std::make_shared<Stage>();

		if (m_select == SelectScene::kStage1)
		{
			return std::make_shared<SceneStage1>(pPlayer, pCamera, pStage);
		}
		else if (m_select == SelectScene::kStage2)
		{
			return std::make_shared<SceneStage2>(pPlayer, pCamera, pStage);
		}
		else if (m_select == kTitle)
		{
			return std::make_shared<SceneTitle>();
		}
	}

	return shared_from_this();
}


/// <summary>
/// 描画
/// </summary>
void SceneSelectStage::Draw()
{
#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "ステージ選択画面", 0xffffff);

	int stage1Color = 0xffffff;
	int stage2Color = 0xffffff;
	int titleColor = 0xffffff;
	if(m_select == SelectScene::kStage1) stage1Color = 0xff0000;
	if (m_select == SelectScene::kStage2) stage2Color = 0xff0000;
	if (m_select == SelectScene::kTitle) titleColor = 0xff0000;
	DrawString(0, 20, "ステージ1", stage1Color);
	DrawString(0, 40, "ステージ2", stage2Color);
	DrawString(0, 60, "タイトル", titleColor);
#endif
}


