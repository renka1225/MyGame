#include "DxLib.h"
#include "Player.h"
#include "DxLib.h"
#include "Player.h"
#include "EnemyNinja.h"
#include "EnemyChef.h"
#include "EnemyAbe.h"
#include "Camera.h"
#include "Input.h"
#include "Stage.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "SceneStage2.h"

namespace
{
	constexpr int kMaxBattleNum = 3;	// 最大バトル数
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="player">プレイヤー参照</param>
/// <param name="camera">カメラ参照</param>
/// <param name="pStage">ステージ参照</param>
SceneStage2::SceneStage2(std::shared_ptr<Player> pPlayer, std::shared_ptr<Camera> pCamera, std::shared_ptr<Stage> pStage)
{
	m_pPlayer = pPlayer;
	m_pCamera = pCamera;
	m_pStage = pStage;
	m_pEnemy = std::make_shared<EnemyNinja>();
	m_battleNum = 0;
}


/// <summary>
/// デストラクタ
/// </summary>
SceneStage2::~SceneStage2()
{
}


/// <summary>
/// 初期化
/// </summary>
void SceneStage2::Init()
{
	SceneStageBase::Init();
}


/// <summary>
/// 更新
/// </summary>
/// <param name="input"></param>
/// <returns>遷移先のシーン</returns>
std::shared_ptr<SceneBase> SceneStage2::Update(Input& input)
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
		m_pPlayer->Update(input, *m_pCamera, *m_pEnemy, *m_pStage);
		m_pCamera->Update(input, *m_pPlayer);
		m_pEnemy->Update(*m_pPlayer, *m_pStage);


		// 敵のHPが0になった場合
		if (m_pEnemy->GetHp() <= 0)
		{
			// 次の敵を登場させる
			switch (m_battleNum)
			{
			case 0:	// 2戦目
				m_pEnemy = nullptr;
				m_pEnemy = std::make_shared<EnemyChef>();
				break;
			case 1:	// 3戦目
				m_pEnemy = nullptr;
				m_pEnemy = std::make_shared<EnemyAbe>();
				break;
			case 2: // 敵をすべて倒したら
				// TODO:クリア処理に移行する
				return std::make_shared<SceneClear>();
				break;
			default:
				break;
			}

			m_battleNum++;
		}

		// プレイヤーのHPが0になった場合
		if (m_pPlayer->GetHp() <= 0)
		{
			return std::make_shared<SceneGameover>();
		}
	}

#ifdef _DEBUG
	// シーン遷移
	if (input.IsTriggered("debug_clear"))
	{
		return std::make_shared<SceneClear>();
	}
	else if (m_pPlayer->GetHp() <= 0.0f || input.IsTriggered("debug_gameover"))
	{
		return std::make_shared<SceneGameover>();
	}

#endif

	return shared_from_this();	// 自身のshared_ptrを返す
}


/// <summary>
/// 描画
/// </summary>
void SceneStage2::Draw()
{
	SceneStageBase::Draw();

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "ステージ2", 0xffffff);
#endif
}
