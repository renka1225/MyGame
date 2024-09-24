#pragma once
#include "SceneMain.h"

class BgStage1;

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
	// ショットの追加
	virtual bool AddShot(ShotBase* pShot) override;
	//　敵の生成
	virtual void CreateEnemy() override;
	// 弾数、敵数等の表示
	virtual void DrawInfo() override;

	// アイテムドロップ
	virtual void DropHpSmallRecovery(int enemyIndex) override;		// HP小回復
	virtual void DropHpGreatRecovery(int enemyIndex) override;		// HP大回復
	virtual void DropShotSmallRecovery(int enemyIndex) override;	// 弾小回復
	virtual void DropShotGreatRecovery(int enemyIndex) override;	// 弾大回復
	virtual void DropLifeRecovery(int enemyIndex) override;			// 残機回復
	virtual void DropFullHpRecovery() override;						// HP全回復

private:
	// 背景のポインタ
	BgStage1* m_pBg;
};

