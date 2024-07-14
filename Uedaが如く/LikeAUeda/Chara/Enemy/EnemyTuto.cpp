#include "DxLib.h"
#include "Player.h"
#include "UIGauge.h"
#include "EnemyTuto.h"

// 定数
namespace
{
	// 敵情報
	const char* const kfileName = "data/Model/enemy.mv1";	// 敵のファイル名
	constexpr float kScale = 0.25f;							// 拡大率
	constexpr float kMaxHp = 1000.0f;						// 最大HP
	const VECTOR kInitPos = VGet(0.0f, 10.0f, 5.0f);		// 初期位置

	// 当たり判定情報
	constexpr float kHitHeight = 50.0f;	     // 当たり判定カプセルの高さ
	constexpr float kHitRadius = 8.0f;	     // 当たり判定カプセルの半径
}


/// <summary>
/// コンストラクタ
/// </summary>
EnemyTuto::EnemyTuto()
{
	m_hp = kMaxHp;
	m_modelHandle = MV1LoadModel(kfileName);
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
}


/// <summary>
/// デストラクタ
/// </summary>
EnemyTuto::~EnemyTuto()
{
	MV1DeleteModel(m_modelHandle);
}


/// <summary>
/// 初期化
/// </summary>
void EnemyTuto::Init()
{
	MV1SetPosition(m_modelHandle, kInitPos);
}


/// <summary>
/// 更新
/// </summary>
void EnemyTuto::Update(Player& player)
{
	// プレイヤーとの当たり判定をチェックする
	player.CheckHitEnemyCol(*this, VGet(m_pos.x, m_pos.y + kHitHeight, m_pos.z), m_pos, kHitRadius);
}


/// <summary>
/// 描画
/// </summary>
void EnemyTuto::Draw()
{
	// 敵モデル描画
	MV1DrawModel(m_modelHandle);

	// HPゲージを表示
	m_pUIGauge->DrawEnemyHp(m_hp, kMaxHp);

#ifdef _DEBUG
	// 敵座標デバッグ表示
	DrawFormatString(0, 60, 0xffffff, "敵座標(x:%f, y:%f, z:%f)", m_pos.x, m_pos.y, m_pos.z);
	DrawFormatString(0, 80, 0xffffff, "hp:%f", m_hp);

	// 当たり判定描画
	DrawCapsule3D(m_pos, VGet(m_pos.x, m_pos.y + kHitHeight , m_pos.z), kHitRadius, 1, 0x0000ff, 0xffffff, false);
#endif

}

/// <summary>
/// プレイヤーとの当たり判定をチェックする
/// </summary>
/// <param name="player"></param>
/// <param name="eCapPosTop"></param>
/// <param name="eCapPosBottom"></param>
/// <param name="eCapRadius"></param>
void EnemyTuto::CheckCollision(Player& player, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius)
{
}
