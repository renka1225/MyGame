#pragma once
#include "SceneBase.h"
#include "DxLib.h"
#include <vector>

class ManagerFont;
class ManagerModel;
class Background;
class Map;
class Player;
class Enemy;
class Camera;

/// <summary>
/// プレイ中のシーン
/// </summary>
class ScenePlaying : public SceneBase
{
public:
	ScenePlaying();
	virtual ~ScenePlaying() {};

	virtual void Init();
	virtual std::shared_ptr<SceneBase> Update(Input& input);
	virtual void Draw();
	virtual void End();

private:
	void LoadEnemy();				// 敵情報読み込み
	void IsCollision(int enemyIdx);	// プレイヤーと敵の当たり判定処理

private:
	// ポインタ
	std::shared_ptr<ManagerFont> m_pFont;
	std::shared_ptr<ManagerModel> m_pModel;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Map> m_pMap;
	std::shared_ptr<Background> m_pBackground;
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;

	int m_time; // 時間

	std::vector<VECTOR> m_enemyPos;	// 敵位置

private:	// 定数
	
	static constexpr int kClearTime = 60 * 90;	// ゲーム時間
	static constexpr int kIntervalTime = 20;	// 経過時間の表示間隔
	static constexpr int kEnemyNum = 10;		// 最大敵数
};