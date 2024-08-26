#include "DxLib.h"
#include "Vec2.h"
#include "Font.h"
#include "UI.h"
#include "CharacterBase.h"
#include "UIBattle.h"
#include <string>

// 定数
namespace
{
	const char* kBarHandlePath = "data/UI/Gauge.png";				// ゲージ画像のパス
	const char* kSilhouetteHandlePath = "data/UI/silhouette.png";	// シルエット画像のパス
	const Vec2 kESilhouettePos = { 1700.0f, 870.0f };				// 敵キャラクターのシルエット位置
	constexpr int kSilhouetteWidth = 268;							// キャラクターのシルエット画像幅
	constexpr int kSilhouetteHeight = 213;							// キャラクターのシルエット画像高さ

	constexpr int kHpColor = 0xff0000;								// HPバーの色
	constexpr int kDamageHpColor = 0xffd700;						// ダメージ時のHPバーの色
	constexpr int kpGaugeColor = 0x0000ff;							// ゲージバーの色
	constexpr int kIntervalTime = 50;								// HPバーが減少するまでの時間

	/*試合開始時*/
	const char* const kFightTextPath = "data/UI/Fight!.png"; // "Fight"のテキスト画像のパス
	const char* const kNumTextPath = "data/UI/number.png";	 // 数字の画像のパス

	constexpr int kFightTextDispStart = 80;					 // "Fight"のテキストを表示し始める時間
	const Vec2 kFightTextPos = { 960, 550 };				 // "Fight"のテキスト位置
	constexpr float kFightTextScele = 0.6f;					 // "Fight"のテキストサイズ
	const Vec2 kMatcheNumTextPos = { 850, 600 };			 // 現在の試合数表示位置
	constexpr int kMatchNumTextWidth = 260;					 // 1つ当たりのテキストの幅
	constexpr int kMatchNumTextInterval = 70;				 // テキストの表示間隔
	constexpr int kTextAdj = 60;							 // テキストの表示間隔調整
	constexpr float kMatchNumTextScele = 0.5f;				 // 試合数のテキストサイズ

	/*プレイヤーUI*/
	const Vec2 kPlayerHpBarLT = { 25.0f, 50.0f };			 // HPバー左上位置
	const Vec2 kPlayerHpBarRB = { 1000.0f, 80.0f };			 // HPバー右下位置
	const Vec2 kPlayerCurrentHpLT = { 50.0f, 56.0f };		 // 現在のHP左上位置
	constexpr float kPlayerHpWidth = 907.0f;				 // HPバーの横幅
	constexpr float kPlayerHpHeight = 18.0f;				 // HPバーの縦幅
		
	const Vec2 kPlayerGaugeBarLT = { 25.0f, 95.0f };		 // ゲージバー左上位置
	const Vec2 kPlayerGaugeBarRB = { 800.0f, 120.0f };		 // ゲージバー右下位置
	const Vec2 kPlayerCurrentGaugeLT = { 40.0f, 100.0f };	 // 現在のゲージ量左上位置
	constexpr float kPlayerGaugeWidth = 727.0f;				 // ゲージバーの横幅
	constexpr float kPlayerGaugeHeight = 15.0f;				 // ゲージバーの縦幅

	/*敵UI*/
	const Vec2 kEnemyHpBarLT = { 850.0f, 970.0f };			 // HPバー左上位置
	const Vec2 kEnemyHpBarRB = { 1850.0f, 1000.0f };		 // HPバー右下位置
	const Vec2 kEnemyCurrentHpLT = { 885.0f, 976.0f };		 // 現在のHP左上位置
	constexpr float kEnemyHpWidth = 920.0f;					 // HPバーの横幅
	constexpr float kEnemyHpHeight = 17.0f;					 // HPバーの縦幅

	/*操作説明画面*/
	const Vec2 kOperationFramePos = { 1720.0f, 280.0f };	 // 枠表示位置
	constexpr float kOperationWidth = 300.0f;				 // 枠の横幅
	constexpr float kOperationHeight = 350.0f;				 // 枠の縦幅
	constexpr int kOperationBackColor = 0x000000;			 // 枠の背景色
	const Vec2 kOperationTextPos = { 1730.0f, 300.0f };		 // テキストの表示位置
	const Vec2 kOperationButtonPos = { 1880.0f, 320.0f };	 // ボタン位置
	constexpr int kButtonSize = 32;						 	 // ボタン画像のサイズ
	constexpr float kOperationButtonScale = 1.0f;		 	 // ボタンの拡大率
	constexpr float kOperationInterval = 40.0f;				 // 表示間隔
	constexpr int kTextColor = 0xffffff;					 // テキストの色

	/*必殺技*/
	const Vec2 kSpecialAttackButtonPos = { 760.0f, 140.0f }; // ボタン位置 
	constexpr float kSpecialAttackButtonScale = 1.2f;		 // ボタン拡大率
	const Vec2 kSpecialAttackTextPos = { 620.0f, 120.0f };	 // テキスト位置
	constexpr int kSpecialAttackTextColor = 0x1470cc;		 // テキストの色
	constexpr int kSpecialAttackTextEdgeColor = 0x0a3866;	 // テキスト縁の色
	constexpr int kMaxPal = 255;							 // 最大加算値

	/*チュートリアル*/
	const Vec2 kTutoTextPos = { 1300.0f, 770.0f };			// テキスト位置
	const Vec2 kTutoButtonPos = { 1390.0f, 790.0f };		// ボタン位置
	constexpr float kTutoButtonScale = 1.2f;				// ボタン拡大率
}

/// <summary>
/// コンストラクタ
/// </summary>
UIBattle::UIBattle():
	m_decreaseHp(0),
	m_currentHp(0),
	m_maxHp(0),
	m_damage(0.0f),
	m_intervalTime(0),
	m_gaugeBarHandle(-1),
	m_silhouetteHandle(-1)
{
	m_fightTextHandle = LoadGraph(kFightTextPath);
	m_numTextHandle = LoadGraph(kNumTextPath);
}


/// <summary>
/// 引数つきコンストラクタ
/// </summary>
UIBattle::UIBattle(float maxHp):
	m_decreaseHp(maxHp),
	m_currentHp(maxHp),
	m_maxHp(maxHp),
	m_damage(0.0f),
	m_intervalTime(0),
	m_fightTextHandle(-1),
	m_numTextHandle(-1)
{
	m_gaugeBarHandle = LoadGraph(kBarHandlePath);
	m_silhouetteHandle = LoadGraph(kSilhouetteHandlePath);
}


/// <summary>
/// デストラクタ
/// </summary>
UIBattle::~UIBattle()
{
	DeleteGraph(m_gaugeBarHandle);
	DeleteGraph(m_silhouetteHandle);
	DeleteGraph(m_fightTextHandle);
	DeleteGraph(m_numTextHandle);
}


/// <summary>
/// 更新
/// </summary>
void UIBattle::UpdateHpBar()
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
/// ダメージを受けた際にタイマーをセットする
/// </summary>
void UIBattle::SetDamageTimer()
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
void UIBattle::OnDamage(float damage)
{
	m_damage += damage;
	SetDamageTimer();
}


/// <summary>
/// スタート時の演出表示
/// </summary>
/// <param name="time">経過時間</param>
/// <param name="matchNum">現在の試合数</param>
/// <param name="maxMatch">最大試合数</param>
void UIBattle::DrawStartProduction(int time, int matchNum, int maxMatch)
{
	if (time > kFightTextDispStart)
	{
		int sizeW, sizeH;
		GetGraphSize(m_numTextHandle, &sizeW, &sizeH);
		// 現在の試合数を表示
		DrawRectRotaGraphF(kMatcheNumTextPos.x, kMatcheNumTextPos.y,
			kMatchNumTextWidth * matchNum, 0, kMatchNumTextWidth, sizeH,
			kMatchNumTextScele, 0.0f, m_numTextHandle, true);
		// /表示
		DrawRectRotaGraphF(kMatcheNumTextPos.x + kMatchNumTextInterval, kMatcheNumTextPos.y,
			sizeW - kMatchNumTextWidth, 0, kMatchNumTextWidth, sizeH,
			kMatchNumTextScele, 0.0f, m_numTextHandle, true);
		// 最大試合数を表示
		DrawRectRotaGraphF(kMatcheNumTextPos.x + kMatchNumTextInterval * 2 + kTextAdj, kMatcheNumTextPos.y,
			kMatchNumTextWidth * (maxMatch - 1), 0, kMatchNumTextWidth, sizeH,
			kMatchNumTextScele, 0.0f, m_numTextHandle, true);
	}
	// "Fight!"の文字を表示
	else if (time < kFightTextDispStart && time > 0)
	{
		int sizeW, sizeH;
		GetGraphSize(m_fightTextHandle, &sizeW, &sizeH);
		DrawRectRotaGraphF(kFightTextPos.x, kFightTextPos.y, 0, 0, sizeW, sizeH, kFightTextScele, 0.0f, m_fightTextHandle, true);
	}
}


/// <summary>
/// プレイヤーのHPバー表示
/// </summary>
/// <param name="currentHp">現在のHP</param>
/// <param name="MaxHp">最大HP</param>
void UIBattle::DrawPlayerHP(float currentHp)
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
void UIBattle::DrawPlayerGauge(float currentGauge, float MaxGauge)
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
void UIBattle::DrawEnemyHp(float currentHp)
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
void UIBattle::DrawSilhouette(int charType)
{
	DrawRectRotaGraphF(kESilhouettePos.x, kESilhouettePos.y, kSilhouetteWidth * charType, 0, kSilhouetteWidth, kSilhouetteHeight, 1.0f, 0.0f, m_silhouetteHandle, true);
}


/// <summary>
/// 必殺技のテキスト表示
/// </summary>
void UIBattle::DrawSpecialAttack()
{
	DrawStringFToHandle(kSpecialAttackTextPos.x, kSpecialAttackTextPos.y, "必殺技", kSpecialAttackTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kSpecialAttack)], kSpecialAttackTextEdgeColor);
	SetDrawBlendMode(DX_BLENDMODE_ADD, kMaxPal);
	DrawStringFToHandle(kSpecialAttackTextPos.x, kSpecialAttackTextPos.y, "必殺技", kSpecialAttackTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kSpecialAttack)]);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// ボタン画像表示
	DrawRectRotaGraphF(kSpecialAttackButtonPos.x, kSpecialAttackButtonPos.y, kButtonSize * ButtonKind::kBButton, 0, kButtonSize, kButtonSize, kSpecialAttackButtonScale, 0.0f, m_buttonHandle, true);
}


/// <summary>
/// 操作説明を表示
/// </summary>
void UIBattle::DrawOperation()
{
	// 背景を薄く表示する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBoxAA(kOperationFramePos.x, kOperationFramePos.y, kOperationFramePos.x + kOperationWidth, kOperationFramePos.y + kOperationHeight, kOperationBackColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// テキスト表示
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kMove,
		"移動", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kCameraMove,
		"カメラ移動", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kPunch,
		"パンチ", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kKick,
		"キック", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kAvoid,
		"回避", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kGuard,
		"ガード", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kRockon,
		"ロックオン", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);
	DrawStringFToHandle(kOperationTextPos.x, kOperationTextPos.y + kOperationInterval * OperationOrder::kPause,
		"ポーズ", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kOperation)]);

	// ボタン画像表示
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kMove,
		kButtonSize * ButtonKind::kRStick, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);		// Rスティック
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kCameraMove,
		kButtonSize * ButtonKind::kLStick, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);		// Lスティック
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kPunch,
		kButtonSize * ButtonKind::kXButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// X
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kKick,
		kButtonSize * ButtonKind::kYButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// Y
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kAvoid,
		kButtonSize * ButtonKind::kAButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// A
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kGuard,
		kButtonSize * ButtonKind::kLBButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// LB
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kRockon,
		kButtonSize * ButtonKind::kRBButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// RB
	DrawRectRotaGraphF(kOperationButtonPos.x, kOperationButtonPos.y + kOperationInterval * OperationOrder::kPause,
		kButtonSize * ButtonKind::kMenuButton, 0, kButtonSize, kButtonSize, kOperationButtonScale, 0.0f, m_buttonHandle, true);	// Menu
}


/// <summary>
/// チュートリアル画面のボタン表示
/// </summary>
void UIBattle::DrawTutoButtonText()
{
	// テキスト表示
	DrawStringFToHandle(kTutoTextPos.x, kTutoTextPos.y,
		"次へ", kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kTutoButton)]);

	// ボタン画像表示
	DrawRectRotaGraphF(kTutoButtonPos.x, kTutoButtonPos.y, kButtonSize * ButtonKind::kAButton, 0, kButtonSize, kButtonSize, kTutoButtonScale, 0.0f, m_buttonHandle, true);
}
