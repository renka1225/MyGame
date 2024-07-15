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
	constexpr float kHitHeight = 50.0f;						// 当たり判定カプセルの高さ
	constexpr float kHitRadius = 8.0f;						// 当たり判定カプセルの半径
	constexpr float kHitAimRadius = 4.0f;					// 腕の当たり判定カプセルの長さ
	constexpr float kHitLegRadius = 5.0f;					// 足の当たり判定カプセルの長さ
	const VECTOR kArmOffset = VGet(0.0f, 0.0f, 0.0f);		// 腕の当たり判定位置
	const VECTOR kArmEndOffset = VGet(0.0f, 0.0f, 0.0f);	// 腕の当たり判定終了位置
	const VECTOR kLegOffset = VGet(0.0f, 0.0f, 0.0f);		// 脚の当たり判定位置
	const VECTOR kLegEndOffset = VGet(0.0f, 0.0f, 0.0f);	// 脚の当たり判定終了位置
}


/// <summary>
/// コンストラクタ
/// </summary>
EnemyTuto::EnemyTuto()
{
	m_hp = kMaxHp;
	m_pos = kInitPos;
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
	// 角度を更新
	UpdateAngle(player);

	// 当たり判定の位置更新
	UpdateCol();

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
	DrawCapsule3D(m_col.hitTopPos, m_col.hitBottomPos, kHitRadius, 1, 0x0000ff, 0xffffff, false);	// 全身
	DrawCapsule3D(m_col.armStartPos, m_col.armEndPos, kHitAimRadius, 1, 0xff00ff, 0xffffff, false);	// 腕
	DrawCapsule3D(m_col.legStartPos, m_col.legEndPos, kHitLegRadius, 1, 0xffff00, 0xffffff, false);	// 脚
#endif

}


/// <summary>
/// 当たり判定位置の更新
/// </summary>
void EnemyTuto::UpdateCol()
{
	// プレイヤーの向きをもとに当たり判定の位置を調整する
	MATRIX rotationMatrix = MGetRotY(m_angle);

	// プレイヤー全体の当たり判定位置を更新
	m_col.hitTopPos = VAdd(m_pos, (VTransform(VGet(0.0f, kHitHeight, 0.0f), rotationMatrix)));
	m_col.hitBottomPos = m_pos;

	// 腕の当たり判定位置を更新
	m_col.armStartPos = VAdd(m_pos, (VTransform(kArmOffset, rotationMatrix)));
	m_col.armEndPos = VAdd(m_col.armStartPos, (VTransform(kArmEndOffset, rotationMatrix)));

	// 脚の当たり判定位置を更新
	m_col.legStartPos = VAdd(m_pos, (VTransform(kLegOffset, rotationMatrix)));
	m_col.legEndPos = VAdd(m_col.legStartPos, (VTransform(kLegEndOffset, rotationMatrix)));
}
