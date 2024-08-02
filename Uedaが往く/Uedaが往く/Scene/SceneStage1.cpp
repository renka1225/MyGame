#include "DxLib.h"
#include "Player.h"
#include "EnemyTuto.h"
#include "Camera.h"
#include "Input.h"
#include "Vec2.h"
#include "Stage.h"
#include "SceneClear.h"
#include "SceneGameover.h"
#include "SceneStage1.h"

namespace
{
	const char* const kFightTextPath = "data/UI/Fight!.png";	// "Fight"のテキスト画像のファイル位置
	const Vec2 kFightTextPos = { 900, 500 };					// "Fight"のテキスト位置
	constexpr float kFightTextScele = 0.6f;						// "Fight"のテキストサイズ
	constexpr int kFightTextDispStart = 80;						// "Fight"のテキストを表示し始める時間

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
	m_battleNum = kMaxBattleNum;
	m_nextBattleTime = kNextBattleTime;
	m_fightTextHandle = LoadGraph(kFightTextPath);
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
		m_pPlayer->Update(input, *m_pCamera, *m_pEnemy, *m_pStage);
		m_pCamera->Update(input, *m_pPlayer);
		m_pEnemy->Update(*m_pPlayer, *m_pStage);

		// 敵のHPが0になった場合
		if (m_pEnemy->GetHp() <= 0)
		{
			return std::make_shared<SceneClear>();
		}
		// プレイヤーのHPが0になった場合
		if (m_pPlayer->GetHp() <= 0)
		{
			return std::make_shared<SceneGameover>();
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
		return std::make_shared<SceneGameover>();
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

	if (m_nextBattleTime < kFightTextDispStart && m_nextBattleTime > 0)
	{
		int sizeW, sizeH;
		GetGraphSize(m_fightTextHandle, &sizeW, &sizeH);
		DrawRectRotaGraphF(kFightTextPos.x, kFightTextPos.y, 0, 0, sizeW, sizeH, kFightTextScele, 0.0f, m_fightTextHandle, true);
	}

#ifdef _DEBUG	// デバッグ表示
	// 現在のシーン
	DrawString(0, 0, "ステージ1", 0xffffff);
#endif
}