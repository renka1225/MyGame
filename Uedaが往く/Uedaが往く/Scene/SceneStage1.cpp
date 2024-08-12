#include "DxLib.h"
#include "Vec2.h"
#include "Input.h"
#include "UIProduction.h"
#include "EffectManager.h"
#include "Player.h"
#include "EnemyTuto.h"
#include "Camera.h"
#include "Stage.h"
#include "ScenePause.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "SceneStage1.h"

namespace
{
	constexpr int kMaxBattleNum = 1;							// 最大バトル数
	constexpr int kNextBattleTime = 150;						// 次の試合が始まるまでの時間
}

/// <summary>
/// コンストラクタ
/// </summary>
SceneStage1::SceneStage1(std::shared_ptr<Player> pPlayer, std::shared_ptr<Camera> pCamera, std::shared_ptr<Stage> pStage)
{
	m_pPlayer = pPlayer;
	m_pCamera = pCamera;
	m_pStage = pStage;
	m_pEnemy = std::make_shared<EnemyTuto>();
	m_battleNum = 0;
	m_nextBattleTime = kNextBattleTime;
}


/// <summary>
/// デストラクタ
/// </summary>
SceneStage1::~SceneStage1()
{
}


/// <summary>
/// 初期化
/// </summary>
void SceneStage1::Init()
{
	SceneStageBase::Init();
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input">入力状態</param>
/// <returns>遷移するシーン</returns>
std::shared_ptr<SceneBase> SceneStage1::Update(Input& input)
{
#ifdef _DEBUG	// デバッグモード
	// Pキーでポーズ、ポーズ中にPでコマ送り
	if (m_debugState == DebugState::Normal && input.IsTriggered("debug_pause"))
	{
		m_debugState = DebugState::Pause;
	}
	if (m_debugState == DebugState::Pause && input.IsTriggered("debug_enter"))
	{
		m_debugState = DebugState::Normal;
	}
	if (m_debugState != DebugState::Pause || input.IsTriggered("debug_pause"))
#endif
	{
		// ポーズ画面を開く
		if (input.IsTriggered("pause"))
		{
			return std::make_shared<ScenePause>(shared_from_this());
		}

		m_nextBattleTime--; // 次の試合が始まるまでの時間

		m_pCamera->Update(input, *m_pPlayer);
		m_pPlayer->Update(input, *m_pCamera, *m_pEnemy, *m_pStage);
		m_pEnemy->Update(*m_pPlayer, *m_pStage, *this);
		if (m_nextBattleTime > 0) return shared_from_this();

		m_elapsedTime++; // 経過時間を進める

		m_pEffect->Update(input, *m_pPlayer, *m_pEnemy); // エフェクト更新

		// 敵のHPが0になった場合
		if (m_pEnemy->GetHp() <= 0)
		{
			m_clearTime.push_back(m_elapsedTime);
			return std::make_shared<SceneClear>(m_clearTime);
		}
		// プレイヤーのHPが0になった場合
		if (m_pPlayer->GetHp() <= 0)
		{
			return std::make_shared<SceneGameover>(shared_from_this());
		}
	}

#ifdef _DEBUG
	// 敵のHPを0にする
	m_pEnemy->DebugDamage(input);
	// シーン遷移
	if (input.IsTriggered("debug_clear"))
	{
		return std::make_shared<SceneClear>();
	}
	else if (m_pPlayer->GetHp() <= 0.0f || input.IsTriggered("debug_gameover"))
	{
		return std::make_shared<SceneGameover>(shared_from_this());
	}
#endif

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneStage1::Draw()
{
	SceneStageBase::Draw();

	// 演出UIを表示
	m_pUIProduction->DrawStartProduction(m_nextBattleTime, m_battleNum, kMaxBattleNum);

	//MEMO:輝度を調整する
	//SetDrawBright(128, 128, 128);


#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "ステージ1", 0xffffff);
	DrawFormatString(0, 200, 0xffffff, "%d", m_elapsedTime);
#endif
}