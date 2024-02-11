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
	virtual void Update() override;
	virtual void Draw() override;

	// 弾の更新
	virtual void UpdateShot(Rect playerRect) override;
	// 敵の更新
	virtual void UpdateEnemy(Rect playerRect) override;
	// 回復アイテムの更新
	virtual void UpdateRecovery(Rect playerRect) override;
	// ショットの追加
	virtual bool AddShot(ShotBase* pShot) override;
	// クリア演出
	virtual void UpdateClearStaging() override;
	//　敵の生成
	virtual void CreateEnemy() override;
	// アイテムの生成
	virtual void CreateItem(int enemyIndex) override;
	// 弾数、敵数等の表示
	virtual void DrawInfo() override;
	// 武器切り替え画面表示
	virtual void DrawShotChange() override;
	// ポーズ画面の表示
	virtual void DrawPause() override;
	// スタート演出の描画
	virtual void DrawStartStaging() override;
	// クリア時演出の描画
	virtual void DrawClearStaging() override;

	// アイテムドロップ
	void DropHpSmallRecovery(int enemyIndex);	// HP小回復
	void DropHpGreatRecovery(int enemyIndex);	// HP大回復
	void DropShotSmallRecovery(int enemyIndex);	// 弾小回復
	void DropShotGreatRecovery(int enemyIndex);	// 弾大回復
	void DropLifeRecovery(int enemyIndex);		// 残機回復
	void DropFullHpRecovery();					// HP全回復

private:
	/*ポインタ設定*/
	// 背景
	BgStage1* m_pBg;

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

