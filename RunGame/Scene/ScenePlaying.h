#pragma once
#include "SceneBase.h"
#include "DxLib.h"

class ManagerModel;
class Background;
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
	// ポインタ
	std::shared_ptr<ManagerModel> m_pModel;
	std::shared_ptr<Background> m_pBackground;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<Camera> m_pCamera;

	int m_time; // 時間

	VECTOR m_enemyPos;	// 敵位置

private:	// 定数
	// ゲーム時間
	static constexpr int kClearTime = 60 * 90;
	// 経過時間の表示間隔
	static constexpr int kIntervalTime = 20;
};