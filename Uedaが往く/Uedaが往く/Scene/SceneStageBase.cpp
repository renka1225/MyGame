#include "DxLib.h"
#include "Input.h"
#include "UIProduction.h"
#include "Light.h"
#include "EffectManager.h"
#include "Player.h"
#include "EnemyBase.h"
#include "Camera.h"
#include "Stage.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "SceneStageBase.h"

namespace
{
	const VECTOR kPlayerInitPos = VGet(2600.0f, 69.0f, 4240.0f);  // プレイヤーの初期位置
	const VECTOR kEnemyInitPos = VGet(2660, 69.0f, 4280.0f);	  // 敵の初期位置
	constexpr int kNextBattleTime = 150;						  // 次の試合が始まるまでの時間
}


/// <summary>
/// コンストラクタ
/// </summary>
SceneStageBase::SceneStageBase():
	m_battleNum(0),
	m_nextBattleTime(kNextBattleTime),
	m_elapsedTime(0)
{
	m_pUIProduction = std::make_shared<UIProduction>();
	m_pEffect = std::make_shared<EffectManager>();
	Light::SetLight();
}


/// <summary>
/// 引数つきコンストラクタ
/// </summary>
/// <param name="pPlayer">プレイヤー参照</param>
/// <param name="pCamera">カメラ参照</param>
/// <param name="pStage">ステージ参照</param>
SceneStageBase::SceneStageBase(std::shared_ptr<Player> pPlayer, std::shared_ptr<Camera> pCamera, std::shared_ptr<Stage> pStage):
	m_pPlayer(pPlayer),
	m_pCamera(pCamera),
	m_pStage(pStage),
	m_pEnemy(nullptr),
	m_battleNum(0),
	m_nextBattleTime(0),
	m_elapsedTime(0)
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
	m_pPlayer->Init(kPlayerInitPos);
	m_pCamera->Init();
	m_pEnemy->Init(kEnemyInitPos);
	m_pEffect->Init();
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
	// エフェクト描画
	m_pEffect->Draw();

	// 操作説明を表示
	//m_pUIProduction->DrawOperation();
}


/// <summary>
/// 敵を倒して次試合が始まる前の処理
/// </summary>
void SceneStageBase::UpdateNextBattle()
{
	m_nextBattleTime = kNextBattleTime;
	// 画面上に残ったエフェクトを削除する
	m_pEffect->ClearEffect();
	// プレイヤーの位置、カメラ位置を最初の状態に戻す
	m_pPlayer->Recovery();
	Init();
}
