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
	virtual ~SceneMain();

	virtual void Init();
	virtual void End();
	virtual void Update();
	virtual void Draw();

	// ショットの追加
	bool AddShot(ShotBase* pShot);

	// アイテムドロップ
	void DropHpSmallRecovery(int enemyIndex);	// HP小回復
	void DropHpGreatRecovery(int enemyIndex);	// HP大回復
	void DropShotSmallRecovery(int enemyIndex);	// 弾小回復
	void DropShotGreatRecovery(int enemyIndex);	// 弾大回復
	void DropLifeRecovery(int enemyIndex);		// 残機回復
	void DropFullHpRecovery();					// HP全回復

	// アイテム2号の表示状態を取得
	bool GetIsExistLineMove() const {return m_isExistLineMove; }

	// シーン移動の取得
	bool IsSceneGameOver() const { return m_isSceneGameOver; }	// ゲームオーバー画面
	bool IsSceneClear() const { return m_isSceneClear; }		// クリア画面

private:
	// 敵キャラクターの生成
	void CreateMatasaburo();	// またさぶろうの生成
	void CreateEnemyCat();		// 猫の生成
	void CreateEnemyBird();		// 鳥の生成
	void CreateEnemyBear();		// 熊の生成

private:
	// 弾数、敵数等の表示
	void DrawInfo();
	// ポーズ画面の表示
	void DrawPause();

protected:
	/*ポインタを取得*/
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

	// プレイヤーの現在地
	Vec2 m_playerPos;
	// プレイヤーがE缶を取得したか true:取得した
	bool m_isGetFullHpRecovery;

	// 現在の敵数
	int m_enemyTotalNum; // 現在の合計数
	int m_catNum;	// 猫の数
	int m_bearNum;	// 熊の数
	int m_birdNum;	// 鳥の数

	// アイテム2号が画面上に存在するか
	bool m_isExistLineMove;

	// 敵の種類
	enum EnemyKind
	{
		kEnemyCat,	// 猫
		kEnemyBear,	// 熊
		kEnemyBird	// 鳥
	};
	EnemyKind m_enemyKind;

	// HPの回復バーの長さ
	int m_drawValue;

	// シーン移動するか true:シーン移動する
	bool m_isSceneGameOver;	// ゲームオーバー画面に移動
	bool m_isSceneClear;	// クリア画面に移動

	// フェードイン、アウト
	int m_fadeAlpha;
};

