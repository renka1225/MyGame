#include "DxLib.h"
#include "Player.h"
#include "EnemyBase.h"
#include "Camera.h"
#include "Input.h"
#include "Light.h"
#include "Stage.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "SceneStageBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pPlayer">プレイヤー参照</param>
/// <param name="pCamera">カメラ参照</param>
/// <param name="pStage">ステージ参照</param>
SceneStageBase::SceneStageBase(std::shared_ptr<Player> pPlayer, std::shared_ptr<Camera> pCamera, std::shared_ptr<Stage> pStage):
	m_pPlayer(pPlayer),
	m_pCamera(pCamera),
	m_pStage(pStage),
	m_pEnemy(nullptr),
	m_battleNum(0)
{
}


/// <summary>
/// デストラクタ
/// </summary>
SceneStageBase::~SceneStageBase()
{
	Light::DeleteLight();
}


/// <summary>
/// 初期化
/// </summary>
void SceneStageBase::Init()
{
	m_pPlayer->Init();
	m_pCamera->Init();
	m_pEnemy->Init();
	Light::SetLight();
}


/// <summary>
/// 描画
/// </summary>
void SceneStageBase::Draw()
{
	// ステージ描画
	m_pStage->Draw();
	// プレイヤー描画
	m_pPlayer->Draw();
	// 敵描画
	m_pEnemy->Draw();
}
