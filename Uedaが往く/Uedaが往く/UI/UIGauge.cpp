#include "DxLib.h"
#include "UIGauge.h"

// 定数
namespace
{
	// プレイヤーUI
	constexpr float kPHpDispL = 30.0f;		 // HPバー左表示位置
	constexpr float kPHpDispT = 40.0f;		 // HPバー上表示位置
	constexpr float kPHpWidth = 400.0f;		 // HPバーの横幅
	constexpr float kPHpHeight = 20.0f;		 // HPバーの縦幅

	constexpr float kpGaugeDispL = 30.0f;	 // ゲージバー左表示位置
	constexpr float kpGaugeDispT = 80.0f;	 // ゲージバー上表示位置
	constexpr float kpGaugeWidth = 400.0f;	 // ゲージバーの横幅
	constexpr float kpGaugeHeight = 20.0f;   // ゲージバーの縦幅
	constexpr int kpGaugeColor = 0x0000ff;	 // ゲージバーの色

	// 敵UI
	constexpr float kEHpDispL = 550.0f;		 // HPバー左表示位置
	constexpr float kEHpDispT = 950.0f;		 // HPバー上表示位置
	constexpr float kEHpWidth = 770.0f;		 // HPバーの横幅
	constexpr float kEHpHeight = 30.0f;		 // HPバーの縦幅

	constexpr int kHpColor = 0xff0000;		 // HPバーの色
	constexpr int kDamageHpColor = 0xffd700; // ダメージ時のHPバーの色


	// HPバーが減少するまでの時間
	constexpr int kIntervalTime = 30;
}

/// <summary>
/// コンストラクタ
/// </summary>
UIGauge::UIGauge(float maxHp):
	m_decreaseHp(maxHp),
	m_currentHp(maxHp),
	m_maxHp(maxHp),
	m_damage(0.0f),
	m_intervalTime(0)
{
}


/// <summary>
/// デストラクタ
/// </summary>
UIGauge::~UIGauge()
{
}


/// <summary>
/// 更新
/// </summary>
void UIGauge::UpdateHpBar()
{
	if (m_intervalTime >= 0)
	{
		m_intervalTime--;
	}
	if (m_intervalTime < 0)
	{
		m_currentHp -= m_damage;
		m_damage = 0.0f;
	}
}


/// <summary>
/// プレイヤーのHPバー表示
/// </summary>
/// <param name="currentHp">現在のHP</param>
/// <param name="MaxHp">最大HP</param>
void UIGauge::DrawPlayerHP(float currentHp, float damage)
{
	// 表示するゲージ量を計算する
	// TODO:m_intervalTimeが0になったら赤バーの長さを変更する
	float hpRatio = currentHp / m_maxHp;
	float decreaseHpRatio = (currentHp + m_damage) / m_maxHp;
	float hpLength = kpGaugeWidth * hpRatio;
	float decreaseHpLength = kPHpWidth * decreaseHpRatio;

	// TODO:バーの背景部分は画像にする
	// バーの背景部分
	DrawBoxAA(kPHpDispL, kPHpDispT, kPHpDispL + kPHpWidth, kPHpDispT + kPHpHeight, 0xffffff, false);
	// ダメージを受けた分のバー
	if (m_intervalTime > 0)
	{
		DrawBoxAA(kPHpDispL, kPHpDispT, kPHpDispL + decreaseHpLength, kPHpDispT + kPHpHeight, kDamageHpColor, true);
	}
	// 現在のHPバー
	DrawBoxAA(kPHpDispL, kPHpDispT, kPHpDispL + hpLength, kPHpDispT + kPHpHeight, kHpColor, true);

#ifdef _DEBUG
	DrawFormatString(0, 160, 0xffffff, "ダメージ量:%f", m_damage);
	DrawFormatString(0, 180, 0xffffff, "バーの長さ:%f", decreaseHpLength);
#endif
}


/// <summary>
/// プレイヤーのゲージバー表示
/// </summary>
/// <param name="currentGauge">現在のゲージ量</param>
/// <param name="MaxGauge">最大ゲージ量</param>
void UIGauge::DrawPlayerGauge(float currentGauge, float MaxGauge)
{
	// 表示するゲージ量を計算する
	float hpRatio = currentGauge / MaxGauge;
	float hpLength = kpGaugeWidth * hpRatio;

	DrawBoxAA(kpGaugeDispL, kpGaugeDispT, kpGaugeDispL + kpGaugeWidth, kpGaugeDispT + kpGaugeHeight, 0xffffff, false);
	DrawBoxAA(kpGaugeDispL, kpGaugeDispT, kpGaugeDispL + hpLength, kpGaugeDispT + kpGaugeHeight, kpGaugeColor, true);
}


/// <summary>
/// 敵のHPバーを表示
/// </summary>
/// <param name="currentHp"></param>
/// <param name="MaxHp"></param>
void UIGauge::DrawEnemyHp(float currentHp, float damage)
{
	// 表示するゲージ量を計算する
	float hpRatio = currentHp / m_maxHp;
	float hpLength = kEHpWidth * hpRatio;
	float decreaseHpRatio = m_decreaseHp / m_maxHp;
	float decreaseHpLength = kPHpWidth * decreaseHpRatio;

	DrawBoxAA(kEHpDispL, kEHpDispT, kEHpDispL + kEHpWidth, kEHpDispT + kEHpHeight, 0xffffff, false);
	// ダメージを受けた分のバー
	if (m_intervalTime > 0)
	{
		DrawBoxAA(kEHpDispL, kEHpDispT, kEHpDispL + decreaseHpLength, kEHpDispT + kEHpHeight, kDamageHpColor, true);
	}
	DrawBoxAA(kEHpDispL, kEHpDispT, kEHpDispL + hpLength, kEHpDispT + kEHpHeight, kHpColor, true);
}


/// <summary>
/// ダメージを受けた際にタイマーをセットする
/// </summary>
void UIGauge::SetDamageTimer()
{
	if (m_intervalTime <= 0)
	{
		m_intervalTime = kIntervalTime;
	}
}


/// <summary>
/// ダメージを受けた時の処理
/// </summary>
/// <param name="damage">受けたダメージ量</param>
void UIGauge::OnDamage(float damage)
{
	m_damage += damage;
	SetDamageTimer();
}
