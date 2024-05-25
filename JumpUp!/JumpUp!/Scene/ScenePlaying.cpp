#include "DxLib.h"
#include "ScenePlaying.h"
#include "Player.h"
#include "Camera.h"
#include "Stage.h"

/// <summary>
/// コンストラクタ
/// </summary>
ScenePlaying::ScenePlaying()
{
	m_pPlayer = std::make_shared<Player>();
	m_pCamera = std::make_shared<Camera>();
	m_pStage = std::make_shared<Stage>();
}


/// <summary>
/// デストラクタ
/// </summary>
ScenePlaying::~ScenePlaying()
{
}


/// <summary>
/// 初期化
/// </summary>
void ScenePlaying::Init()
{
	m_pPlayer->Init();
	m_pCamera->Init();
	m_pStage->Init();
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力</param>
/// <returns>遷移先のポインタ</returns>
std::shared_ptr<SceneBase> ScenePlaying::Update(Input& input)
{
	// カメラ更新
	m_pCamera->Update(input);

	// ステージ更新
	m_pStage->Update();

	// プレイヤー更新
	m_pPlayer->SetCameraAngle(m_pCamera->GetAngle());
	m_pPlayer->Update(input, m_pStage);

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void ScenePlaying::Draw()
{
#ifdef _DEBUG		// デバッグ表示
	// 現在のシーン
	DrawFormatString(0, 0, 0xffffff, "プレイ画面");
	// グリッド表示
	m_pDrawDebug.DrawGrid();
#endif

	// ステージ描画
	m_pStage->Draw();

	// プレイヤー描画
	m_pPlayer->Draw(m_pDrawDebug);
}
