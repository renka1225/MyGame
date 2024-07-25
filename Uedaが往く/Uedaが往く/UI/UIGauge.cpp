#include "DxLib.h"
#include "Vec2.h"
#include "UIGauge.h"

// 定数
namespace
{
	// プレイヤーUI
	const Vec2 kPlayerHpBarLT = { 25.0f, 40.0f };			// HPバー左上位置
	const Vec2 kPlayerHpBarRB = { 600.0f, 100.0f };			// HPバー右下位置
	const Vec2 kPlayerCurrentHpLT = { 40.0f, 55.0f };		// 現在のHP左上位置
	constexpr float kPlayerHpWidth = 540.0f;				// HPバーの横幅
	constexpr float kPlayerHpHeight = 32.0f;				// HPバーの縦幅
		
	const Vec2 kPlayerGaugeBarLT = { 25.0f, 110.0f };		// ゲージバー左上位置
	const Vec2 kPlayerGaugeBarRB = { 600.0f, 140.0f };		// ゲージバー右下位置
	const Vec2 kPlayerCurrentGaugeLT = { 40.0f, 118.0f };	// 現在のゲージ量左上位置
	constexpr float kPlayerGaugeWidth = 520.0f;				// ゲージバーの横幅
	constexpr float kPlayerGaugeHeight = 16.0f;				// ゲージバーの縦幅
	constexpr int kpGaugeColor = 0x0000ff;					// ゲージバーの色

	// 敵UI
	const Vec2 kEnemyHpBarLT = { 535.0f, 935.0f };		// HPバー左上位置
	const Vec2 kEnemyHpBarRB = { 1300.0f, 1000.0f };	// HPバー右下位置
	const Vec2 kEnemyCurrentHpLT = { 560.0f, 952.0f };	// 現在のHP左上位置
	constexpr float kEnemyHpWidth = 710.0f;				// HPバーの横幅
	constexpr float kEnemyHpHeight = 32.0f;				// HPバーの縦幅

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
	m_gaugeBarHandle = LoadGraph("data/UI/Gauge.png");
}


/// <summary>
/// デストラクタ
/// </summary>
UIGauge::~UIGauge()
{
	DeleteGraph(m_gaugeBarHandle);
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
void UIGauge::DrawPlayerHP(float currentHp)
{
	// 表示するゲージ量を計算する
	float hpRatio = currentHp / m_maxHp;
	float decreaseHpRatio = (currentHp + m_damage) / m_maxHp;
	float hpLength = kPlayerHpWidth * hpRatio;
	float decreaseHpLength = kPlayerHpWidth * decreaseHpRatio;

	// バーの背景部分
	DrawExtendGraphF(kPlayerHpBarLT.x, kPlayerHpBarLT.y, kPlayerHpBarRB.x, kPlayerHpBarRB.y, m_gaugeBarHandle, true);
	// ダメージを受けた分のバー
	if (m_intervalTime > 0)
	{
		DrawBoxAA(kPlayerCurrentHpLT.x, kPlayerCurrentHpLT.y, kPlayerCurrentHpLT.x + decreaseHpLength, kPlayerCurrentHpLT.y + kPlayerHpHeight, kDamageHpColor, true);
	}
	// 現在のHPバー
	DrawBoxAA(kPlayerCurrentHpLT.x, kPlayerCurrentHpLT.y, kPlayerCurrentHpLT.x + hpLength, kPlayerCurrentHpLT.y + kPlayerHpHeight, kHpColor, true);
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
	float hpLength = kPlayerGaugeWidth * hpRatio;

	// バーの背景部分
	DrawExtendGraphF(kPlayerGaugeBarLT.x, kPlayerGaugeBarLT.y, kPlayerGaugeBarRB.x, kPlayerGaugeBarRB.y, m_gaugeBarHandle, true);
	DrawBoxAA(kPlayerCurrentGaugeLT.x, kPlayerCurrentGaugeLT.y, kPlayerCurrentGaugeLT.x + hpLength, kPlayerCurrentGaugeLT.y + kPlayerGaugeHeight, kpGaugeColor, true);
}


/// <summary>
/// 敵のHPバーを表示
/// </summary>
/// <param name="currentHp"></param>
/// <param name="MaxHp"></param>
void UIGauge::DrawEnemyHp(float currentHp)
{
	// 表示するゲージ量を計算する
	float hpRatio = currentHp / m_maxHp;
	float decreaseHpRatio = (currentHp + m_damage) / m_maxHp;
	float hpLength = kEnemyHpWidth * hpRatio;
	float decreaseHpLength = kEnemyHpWidth * decreaseHpRatio;

	// バーの背景部分
	DrawExtendGraphF(kEnemyHpBarLT.x, kEnemyHpBarLT.y, kEnemyHpBarRB.x, kEnemyHpBarRB.y, m_gaugeBarHandle, true);
	// ダメージを受けた分のバー
	if (m_intervalTime > 0)
	{
		DrawBoxAA(kEnemyCurrentHpLT.x, kEnemyCurrentHpLT.y, kEnemyCurrentHpLT.x + decreaseHpLength, kEnemyCurrentHpLT.y + kEnemyHpHeight, kDamageHpColor, true);
	}
	DrawBoxAA(kEnemyCurrentHpLT.x, kEnemyCurrentHpLT.y, kEnemyCurrentHpLT.x + hpLength, kEnemyCurrentHpLT.y + kEnemyHpHeight, kHpColor, true);
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
