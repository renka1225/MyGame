#include "DxLib.h"
#include "Vec2.h"
#include "CharacterBase.h"
#include "UIGauge.h"

// 定数
namespace
{
	const Vec2 kESilhouettePos = { 1700.0f, 870.0f };		// 敵キャラクターのシルエット位置
	constexpr int kSilhouetteWidth = 268;					// キャラクターのシルエット画像幅
	constexpr int kSilhouetteHeight = 213;					// キャラクターのシルエット画像高さ
	
	constexpr int kHpColor = 0xff0000;						// HPバーの色
	constexpr int kDamageHpColor = 0xffd700;				// ダメージ時のHPバーの色
	constexpr int kpGaugeColor = 0x0000ff;					// ゲージバーの色
	constexpr int kIntervalTime = 50;						// HPバーが減少するまでの時間

	// プレイヤーUI
	const Vec2 kPlayerHpBarLT = { 25.0f, 50.0f };			// HPバー左上位置
	const Vec2 kPlayerHpBarRB = { 1000.0f, 80.0f };			// HPバー右下位置
	const Vec2 kPlayerCurrentHpLT = { 50.0f, 56.0f };		// 現在のHP左上位置
	constexpr float kPlayerHpWidth = 907.0f;				// HPバーの横幅
	constexpr float kPlayerHpHeight = 18.0f;				// HPバーの縦幅
		
	const Vec2 kPlayerGaugeBarLT = { 25.0f, 95.0f };		// ゲージバー左上位置
	const Vec2 kPlayerGaugeBarRB = { 800.0f, 120.0f };		// ゲージバー右下位置
	const Vec2 kPlayerCurrentGaugeLT = { 40.0f, 100.0f };	// 現在のゲージ量左上位置
	constexpr float kPlayerGaugeWidth = 727.0f;				// ゲージバーの横幅
	constexpr float kPlayerGaugeHeight = 15.0f;				// ゲージバーの縦幅

	// 敵UI
	const Vec2 kEnemyHpBarLT = { 850.0f, 970.0f };			// HPバー左上位置
	const Vec2 kEnemyHpBarRB = { 1850.0f, 1000.0f };		// HPバー右下位置
	const Vec2 kEnemyCurrentHpLT = { 885.0f, 976.0f };		// 現在のHP左上位置
	constexpr float kEnemyHpWidth = 920.0f;					// HPバーの横幅
	constexpr float kEnemyHpHeight = 17.0f;					// HPバーの縦幅
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
	m_silhouetteHandle = LoadGraph("data/UI/silhouette.png");
}


/// <summary>
/// デストラクタ
/// </summary>
UIGauge::~UIGauge()
{
	DeleteGraph(m_gaugeBarHandle);
	DeleteGraph(m_silhouetteHandle);
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
	// ダメージを受けた際に表示する
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
/// <param name="currentHp">現在のHP</param>
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
/// シルエット描画
/// </summary>
void UIGauge::DrawSilhouette(int charType)
{
	DrawRectRotaGraphF(kESilhouettePos.x, kESilhouettePos.y, kSilhouetteWidth * charType, 0, kSilhouetteWidth, kSilhouetteHeight, 1.0f, 0.0f, m_silhouetteHandle, true);
}


/// <summary>
/// ダメージを受けた際にタイマーをセットする
/// </summary>
void UIGauge::SetDamageTimer()
{
	if (m_intervalTime < 0)
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
