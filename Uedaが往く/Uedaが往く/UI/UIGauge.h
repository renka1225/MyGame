#pragma once

/// <summary>
/// バトル中に表示するゲージのUIを管理する
/// </summary>
class UIGauge
{
public:
	UIGauge(float maxHp);
	~UIGauge();
	void UpdateHpBar();
	void DrawPlayerHP(float currentHp);							// プレイヤーのHPバーを表示
	void DrawPlayerGauge(float currentGauge, float MaxGauge);	// プレイヤーのゲージバーを表示
	void DrawEnemyHp(float currentHp);							// 敵のHPバーを表示
	void DrawSilhouette(int charType);							// シルエットを表示

	void SetDamageTimer();			// ダメージを受けた際にタイマーをセットする
	void OnDamage(float damage);	// 受けたダメージ量を計算する

private:
	float m_decreaseHp;				// ダメージを受けた後のHP
	float m_currentHp;				// 現在のHP
	float m_damage;					// 受けたダメージ量
	float m_maxHp;					// 最大HP
	int m_intervalTime;				// HPバーが減少するまでの時間
	int m_gaugeBarHandle;			// ゲージバーの画像
	int m_silhouetteHandle;			// キャラクターのシルエット画像
};
