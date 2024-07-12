#include "DxLib.h"
#include "UIGauge.h"

// 定数
namespace
{
	// プレイヤーUI
	constexpr float kPHpDispL = 30.0f;		// HPバー左表示位置
	constexpr float kPHpDispT = 40.0f;		// HPバー上表示位置
	constexpr float kPHpWidth = 400.0f;		// HPバーの横幅
	constexpr float kPHpHeight = 20.0f;		// HPバーの縦幅
	constexpr int kPHpColor = 0xff0000;		// HPバーの色
	constexpr float kpGaugeDispL = 30.0f;	// ゲージバー左表示位置
	constexpr float kpGaugeDispT = 80.0f;	// ゲージバー上表示位置
	constexpr float kpGaugeWidth = 400.0f;	// ゲージバーの横幅
	constexpr float kpGaugeHeight = 20.0f;  // ゲージバーの縦幅
	constexpr int kpGaugeColor = 0x0000ff;	// HPバーの色

	// 敵UI
	constexpr float kEHpDispL = 550.0f;		// HPバー左表示位置
	constexpr float kEHpDispT = 950.0f;		// HPバー上表示位置
	constexpr float kEHpWidth = 770.0f;		// HPバーの横幅
	constexpr float kEHpHeight = 30.0f;		// HPバーの縦幅
	constexpr int kEHpColor = 0xff0000;		// HPバーの色
}

/// <summary>
/// コンストラクタ
/// </summary>
UIGauge::UIGauge()
{
}

/// <summary>
/// デストラクタ
/// </summary>
UIGauge::~UIGauge()
{
}


/// <summary>
/// 初期化
/// </summary>
void UIGauge::Init()
{
}


/// <summary>
/// 更新
/// </summary>
void UIGauge::Update()
{
}


/// <summary>
/// プレイヤーのHPバー表示
/// </summary>
/// <param name="currentHp">現在のHP</param>
/// <param name="MaxHp">最大HP</param>
void UIGauge::DrawPlayerHP(float currentHp, float MaxHp)
{
	// 表示するゲージ量を計算する
	float hpRatio = currentHp / MaxHp;
	float hpLength = kPHpWidth* hpRatio;

	// TODO:バーの背景部分は画像にする
	DrawBoxAA(kPHpDispL, kPHpDispT, kPHpDispL + kPHpWidth, kPHpDispT + kPHpHeight, 0xffffff, false);
	DrawBoxAA(kPHpDispL, kPHpDispT, kPHpDispL + hpLength, kPHpDispT + kPHpHeight, kPHpColor, true);
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

	// TODO:バーの背景部分は画像にする
	DrawBoxAA(kpGaugeDispL, kpGaugeDispT, kpGaugeDispL + kpGaugeWidth, kpGaugeDispT + kpGaugeHeight, 0xffffff, false);
	DrawBoxAA(kpGaugeDispL, kpGaugeDispT, kpGaugeDispL + hpLength, kpGaugeDispT + kpGaugeHeight, kpGaugeColor, true);
}


/// <summary>
/// 敵のHPバーを表示
/// </summary>
/// <param name="currentHp"></param>
/// <param name="MaxHp"></param>
void UIGauge::DrawEnemyHp(float currentHp, float MaxHp)
{
	// 表示するゲージ量を計算する
	float hpRatio = currentHp / MaxHp;
	float hpLength = kEHpWidth * hpRatio;

	// TODO:バーの背景部分は画像にする
	DrawBoxAA(kEHpDispL, kEHpDispT, kEHpDispL + kEHpWidth, kEHpDispT + kEHpHeight, 0xffffff, false);
	DrawBoxAA(kEHpDispL, kEHpDispT, kEHpDispL + hpLength, kEHpDispT + kEHpHeight, kEHpColor, true);
}
