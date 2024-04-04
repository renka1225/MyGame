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
	std::shared_ptr<ManagerModel> m_pModel;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Map> m_pMap;
	std::shared_ptr<Background> m_pBackground;
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;

	int m_time;					// 時間
	int m_noticeDisPlayFrame;	// 経過時間の通知を表示する時間

	std::vector<VECTOR> m_enemyPos;	// 敵位置

private:	// 定数
	static constexpr int kEnemyNum = 10;		// 最大敵数
	static constexpr int kClearTime = 60 * 90;	// ゲーム時間
	// 20秒ごとに時間経過の通知をする
	static constexpr int kNoticeTime1 = 20 * 60;
	static constexpr int kNoticeTime2 = 40 * 60;
	static constexpr int kNoticeTime3 = 60 * 60;
	static constexpr int kNoticeTime4 = 80 * 60;
	static constexpr int kNoticeDisPlayFrame = 3 * 60;	// 通知を表示する時間

	static constexpr int kTimePosX = 640;			// 時間表示位置X
	static constexpr int kTimePosY = 80;			// 時間表示位置Y
	static constexpr int kNoticeTimePosX = 750;		// 時間経過の通知表示位置X
	static constexpr int kNoticeTimePosY = 170;		// 時間経過の通知表示位置Y
};