#pragma once
#include "SceneBase.h"
#include <vector>

class Player;
class Camera;
class Stage;
class EnemyBase;
class UIProduction;
class EffectManager;

/// <summary>
/// プレイシーンの基底クラス
/// </summary>
class SceneStageBase : public SceneBase
{
public:
	SceneStageBase();
	SceneStageBase(std::shared_ptr<Player> pPlayer, std::shared_ptr<Camera> pCamera, std::shared_ptr<Stage> pStage);
	virtual ~SceneStageBase();
	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input) = 0;
	virtual void Draw();
	// 試合が始まるまでの時間を取得
	int GetBattleStartTime() const { return m_nextBattleTime; }

protected:
	void UpdateNextBattle();	// 敵を倒して次試合が始まる前の処理

protected:
	std::shared_ptr<Player> m_pPlayer;				// プレイヤー
	std::shared_ptr<Camera> m_pCamera;				// カメラ
	std::shared_ptr<Stage> m_pStage;				// ステージ
	std::shared_ptr<EnemyBase> m_pEnemy;			// 敵
	std::shared_ptr<UIProduction> m_pUIProduction;	// 演出UI
	std::shared_ptr<EffectManager> m_pEffect;		// エフェクト
	int m_battleNum;								// 現在のバトル数
	int m_nextBattleTime;							// 次の試合が始まるまでの時間
	int m_elapsedTime;								// 経過時間
	std::vector<int> m_clearTime;					// 各試合ごとのクリアタイム
};

