#pragma once
#include "SceneBase.h"

class Player;
class Camera;
class Stage;
class EnemyBase;
class CharacterBase;

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

protected:
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Stage> m_pStage;
	std::shared_ptr<EnemyBase> m_pEnemy;
	int m_battleNum;				// 現在のバトル数
	int m_nextBattleTime;			// 次の試合が始まるまでの時間
	int m_elapsedTime;				// 経過時間
	std::vector<int> m_clearTime;	// 各試合ごとのクリアタイム
	int m_fightTextHandle;			// "Fight"のテキスト画像
};

