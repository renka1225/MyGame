#pragma once
#include <vector>
#include "Vec2.h"
#include "Rect.h"

class FontManager;
class Bg;
class ScenePause;
class Player;
class ShotBase;
class EnemyBase;
class RecoveryBase;
class Fireworks;

/// <summary>
/// ゲーム画面のクラス
/// </summary>
class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// クリア演出の処理
	virtual void UpdateClearStaging();
	// 回復アイテムの更新
	virtual void UpdateRecovery(Rect playerRect);

	// 武器切り替え画面表示
	virtual void DrawShotChange();
	// ポーズ画面の表示
	virtual void DrawPause();
	// スタート演出の描画
	virtual void DrawStartStaging();
	// クリア時演出の描画
	virtual void DrawClearStaging();
	// アイテムの生成
	virtual void CreateItem(int enemyIndex);

	// 弾の更新
	virtual void UpdateShot(Rect playerRect) = 0;
	// 敵の更新
	virtual void UpdateEnemy(Rect playerRect) = 0;
	// ショットの追加
	virtual bool AddShot(ShotBase* pShot) = 0;
	//　敵の生成
	virtual void CreateEnemy() = 0;
	// 弾数、敵数等の表示
	virtual void DrawInfo() = 0;

	// アイテムドロップ
	virtual void DropHpSmallRecovery(int enemyIndex) = 0;	// HP小回復
	virtual void DropHpGreatRecovery(int enemyIndex) = 0;	// HP大回復
	virtual void DropShotSmallRecovery(int enemyIndex) = 0;	// 弾小回復
	virtual void DropShotGreatRecovery(int enemyIndex) = 0;	// 弾大回復
	virtual void DropLifeRecovery(int enemyIndex) = 0;		// 残機回復
	virtual void DropFullHpRecovery() = 0;					// HP全回復

	// アイテム2号の表示状態を取得
	bool GetIsExistLineMove() const { return m_isExistLineMove; }
	// メニューが開かれているか取得する
	bool GetIsExistMenu() const { return m_isExistMenu; }
	// シーン移動の取得
	bool IsSceneGameOver() const { return m_isSceneGameOver; }	// ゲームオーバー画面
	bool IsSceneClear() const { return m_isSceneClear; }		// クリア画面
	bool IsSceneTitle() const { return m_isSceneTitle; }		// タイトル画面
	bool IsSceneEnd() const { return m_isSceneEnd; }			// リトライ

protected:
	/*ポインタを取得*/
	// フォント管理
	FontManager* m_pFont;
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
	// 花火
	//std::vector<Fireworks*> m_pFireworks;

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
	// メニュー、武器切り替え画面が表示されているか
	bool m_isExistMenu;

	// HPの回復バーの長さ
	int m_drawValue;

	// シーン移動するか true:シーン移動する
	bool m_isSceneGameOver;	// ゲームオーバー画面に移動
	bool m_isSceneClear;	// クリア画面に移動
	bool m_isSceneTitle;	// タイトル画面に移動
	bool m_isSceneEnd;		// ゲーム画面を終了
	bool m_isRetry;			// リトライする

	/*演出*/
	// フェードイン、アウト
	int m_fadeAlpha;
	int m_stagingFade; // スタート演出等のフェード

	// スタート演出の表示位置
	Vec2 m_startDis;
	// クリア演出の表示位置
	Vec2 m_clearDis;
	// 花火の表示位置
	Vec2 m_fireworks1Pos;	// 花火1
	Vec2 m_fireworks2Pos;	// 花火2
	Vec2 m_fireworks3Pos;	// 花火3
	Vec2 m_fireworks4Pos;	// 花火4
	Vec2 m_fireworks5Pos;	// 花火5
	Vec2 m_fireworks6Pos;	// 花火6

	float m_startStagingTime;		// スタート演出の時間
	float m_clearStagingTime;		// クリア演出時間
	float m_gameoverStagingTime;	// ゲームオーバー演出時間
	int m_fireworks1Frame;			// 花火1の表示フレーム 
	int m_fireworks2Frame;			// 花火2の表示フレーム 
	int m_fireworks3Frame;			// 花火3の表示フレーム 
	int m_fireworks4Frame;			// 花火4の表示フレーム 
	int m_fireworks5Frame;			// 花火5の表示フレーム 
	int m_fireworks6Frame;			// 花火6の表示フレーム 

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
	int m_metalHandle;		// メタルの画像
	int m_fireHandle;		// ファイアの画像
	int m_lineMoveHandle;	// 2号の画像
	int m_fullHpRecHandle;  // E缶の画像	
	int m_shotSelectHandle;	// 選択中の武器
	int m_startHandle;		// スタート演出の画像
	int m_fireworks1;		// 花火1
	int m_fireworks2;		// 花火2
	int m_fireworks3;		// 花火3

	// 武器切り替え表示
	enum ShotChange
	{
		kShotBuster,	// バスター
		kShotMetal,		// メタル
		kShotFire,		// ファイア
		kShotLineMove,	// 2号
		kRecovery		// E缶
	};

	// ポーズ画面表示
	enum Pause
	{
		kPauseBack,		// ゲームに戻る
		kPauseRetry,	// リトライ
		kPauseTitle		// タイトルに戻る
	};
};

