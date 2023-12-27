#pragma once
#include <vector>
#include "Vec2.h"

class Bg;
class ScenePause;
class Player;
class ShotBase;
class EnemyBase;
class RecoveryBase;

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
	// アイテムの生成
	void DropHpSmallRecovery();

private:
	// グラフィックのハンドル
	int m_bgHandle;			// 背景
	int m_mapHandle;		// マップチップ
	int m_playerHandle;		// プレイヤー
	int m_enemyHandle;		// 敵

	int m_drawValue; // HPの回復バーの長さ

	// シーンを終了させるフラグ true:終了
	bool m_isSceneEnd;

	// 背景
	Bg* m_pBg;
	// ポーズ画面
	ScenePause* m_pPause;
	// プレイヤー
	Player* m_pPlayer;
	// ショット
	std::vector<ShotBase*> m_pShot;
	// 敵
	std::vector<EnemyBase*> m_pEnemy;
	// 回復アイテム
	std::vector<RecoveryBase*> m_pRecovery;
};

