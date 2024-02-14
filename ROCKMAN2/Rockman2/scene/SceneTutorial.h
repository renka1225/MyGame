#pragma once
#include "SceneMain.h"

class BgTutorial;

/// <summary>
/// ステージ1クラス
/// </summary>
class SceneTutorial : public SceneMain
{
public:
	SceneTutorial();
	virtual ~SceneTutorial();

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
	// 背景
	BgTutorial* m_pBg;
};

