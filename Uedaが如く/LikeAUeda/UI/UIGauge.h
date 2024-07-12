#pragma once

/// <summary>
/// バトル中に表示するUI
/// </summary>
class UIGauge
{
public:
	UIGauge();
	~UIGauge();
	void Init();
	void Update();
	void DrawPlayerHP(float currentHp, float MaxHp);			// プレイヤーのHPバーを表示
	void DrawPlayerGauge(float currentGauge, float MaxGauge);	// プレイヤーのゲージバーを表示
};

