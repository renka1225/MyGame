#pragma once
#include "SceneMain.h"

class BgStage1;
class Player;

/// <summary>
/// ステージ1クラス
/// </summary>
class SceneStage1 : public SceneMain
{
public:
	SceneStage1();
	virtual ~SceneStage1();

	virtual void Init() override;
	virtual void End() override;
	virtual void Update() override;
	virtual void Draw() override;

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
	bool GetIsExistLineMove() const { return m_isExistLineMove; }

	// シーン移動の取得
	bool IsSceneGameOver() const { return m_isSceneGameOver; }	// ゲームオーバー画面
	bool IsSceneClear() const { return m_isSceneClear; }		// クリア画面
	bool IsSceneTitle() const { return m_isSceneTitle; }		// タイトル画面
	bool IsSceneEnd() const { return m_isSceneEnd; }			// プレイ画面を終了

private:
	//　敵の生成
	void CreateEnemy();
	// アイテムの生成
	void CreateItem(int enemyIndex);
	// 弾数、敵数等の表示
	void DrawInfo();
	// 武器切り替え画面表示
	void DrawShotChange();
	// ポーズ画面の表示
	void DrawPause();
	// スタート演出の描画
	void DrawStartStaging();
	// クリア時演出の描画
	void DrawClearStaging();

private:
	// フォント管理
	FontManager * m_pFont;
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

	// スタート演出の表示位置
	Vec2 m_startDis;
	// クリア演出の表示位置
	Vec2 m_clearDis;

	// プレイヤーの現在地
	Vec2 m_playerPos;
	// プレイヤーがE缶を取得したか true:取得した
	bool m_isGetFullHpRecovery;

	// 現在の敵数
	int m_enemyTotalNum;
	// 現在のタイム
	float m_time;

	// アイテム2号が画面上に存在するか
	bool m_isExistLineMove;

	// HPの回復バーの長さ
	int m_drawValue;

	// シーン移動するか true:シーン移動する
	bool m_isSceneGameOver;	// ゲームオーバー画面に移動
	bool m_isSceneClear;	// クリア画面に移動
	bool m_isSceneTitle;	// タイトル画面に移動
	bool m_isSceneEnd;		// ゲーム画面を終了
	bool m_isRetry;			// リトライする

	// フェードイン、アウト
	int m_fadeAlpha;
	int m_stagingFade; // スタート演出等のフェード

	// 演出
	float m_startStagingTime;		// スタート演出の時間
	float m_clearStagingTime;		// クリア演出時間
	float m_gameoverStagingTime;	// ゲームオーバー演出時間
	// Readyの表示カウント
	int m_readyCount;
	// 画面揺れ演出
	int m_shakeFrame;
	float m_ampFrame;

	// 音
	int m_bgm;			// BGM
	int m_enemyDeadSE;	// 敵死亡時のSE
	int m_recoverySE;	// 回復時のSE
	int m_lineMoveSE;	// アイテム2号が画面内にあるとき
	int m_startSE;		// スタート時のSE
	int m_clearSE;		// クリア時のSE
	int m_fireworksSE;	// 花火のSE

	// 画像
	int m_gameScreenHandle;	// ゲーム画面
	int m_frameHandle;		// 枠
	int m_shotSelectHandle;	// 選択中の武器
	int m_startHandle;		// スタート演出の画像
	int m_fireworks;		// 花火
};

