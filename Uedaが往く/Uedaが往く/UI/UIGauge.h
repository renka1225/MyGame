#pragma once

/// <summary>
/// バトル中に表示するゲージのUIを管理する
/// </summary>
class UIGauge
{
public:
	UIGauge();
	~UIGauge();
	void UpdatePlayerHp();
	void DrawPlayerHP(float currentHp, float MaxHp);			// プレイヤーのHPバーを表示
	void DrawPlayerGauge(float currentGauge, float MaxGauge);	// プレイヤーのゲージバーを表示
	void DrawEnemyHp(float currentHp, float MaxHp);				// 敵のHPバーを表示
	void SetDamageTimer();										// ダメージを受けた際にタイマーをセットする

private:
	int m_hpBarDecreaseTime;	// HPバーが減少するまでの時間
	float m_decreaseHp;			// 減少するHP量
};
