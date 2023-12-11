#pragma once
#include <vector>
#include "Vec2.h"

class Bg;
class RecoveryBase;
class Player;
class ShotBase;
class EnemyBase;

/// <summary>
/// ゲーム画面のクラス
/// </summary>
class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void End();
	void Update();
	void Draw();

	// ショットの追加
	// 登録できなかった場合はfalseを返す、内部でpShotを解放する
	bool AddShot(ShotBase* pShot);

	// シーンを終了させるか
	bool IsSceneEnd() const { return m_isSceneEnd; }

private:
	// 敵キャラクターの生成
	void CreateMatasaburo(); // またさぶろうの生成

	// 回復アイテムの生成
	void CreateHpRecovery(); // HP回復

private:
	// グラフィックのハンドル
	int m_bgHandle;			// 背景
	int m_playerHandle;		// プレイヤー
	int m_enemyHandle;		// 敵

	// シーンを終了させるフラグ true:終了
	bool m_isSceneEnd;

	// 背景
	Bg* m_pBg;
	// 回復アイテム
	RecoveryBase* m_pRecovery;
	// プレイヤー
	Player* m_pPlayer;
	// ショット
	std::vector<ShotBase*> m_pShot;
	// 敵
	std::vector<EnemyBase*> m_pEnemy;

};

