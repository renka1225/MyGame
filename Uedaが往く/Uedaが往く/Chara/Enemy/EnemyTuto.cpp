#include "DxLib.h"
#include "Player.h"
#include "Stage.h"
#include "UIGauge.h"
#include "LoadData.h"
#include "EnemyTuto.h"

// 定数
namespace
{
	// 敵情報
	const char* const kfileName = "data/Model/enemyTuto.mv1";	// 敵のファイル名
	constexpr float kScale = 0.3f;								// 拡大率
	const VECTOR kInitPos = VGet(0.0f, 10.0f, 5.0f);			// 初期位置
}


/// <summary>
/// コンストラクタ
/// </summary>
EnemyTuto::EnemyTuto()
{
	// キャラクター情報を読み込む
	m_pLoadData = std::make_shared<LoadData>(*this, static_cast<int>(CharaType::kEnemyTuto));

	m_hp = m_status.maxHp;
	m_pos = kInitPos;
	m_moveSpeed = m_status.maxMoveSpeed;
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
void EnemyTuto::Update(Player& player, Stage& stage)
{
	// 移動パラメータを設定する
	VECTOR	upMoveVec;		// 上ボタンを入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	leftMoveVec;	// 左ボタンを入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	moveVec;		// このフレームの移動ベクトル

	// エネミーの状態を更新
	EnemyState prevState = m_currentState;

	// 攻撃処理
	m_currentState = Attack();
	// 移動処理
	m_currentState = UpdateMoveParameter(player, upMoveVec, leftMoveVec, moveVec);

	// プレイヤーとの当たり判定をチェックする
	player.CheckHitEnemyCol(*this, VGet(m_pos.x, m_pos.y + m_colInfo.bodyHeight, m_pos.z), m_pos, m_colInfo.bodyRadius);

	// アニメーション状態を更新
	UpdateAnimState(prevState);

	// 角度を更新
	UpdateAngle(player);

	// 移動ベクトルを元にエネミーを移動させる
	Move(moveVec, player, stage);

	// アニメーション処理の更新
	UpdateAnim();

	// 当たり判定の位置更新
	UpdateCol();
}


/// <summary>
/// 描画
/// </summary>
void EnemyTuto::Draw()
{
	// 敵モデル描画
	MV1DrawModel(m_modelHandle);

	// HPゲージを表示
	m_pUIGauge->DrawEnemyHp(m_hp, m_status.maxHp);

#ifdef _DEBUG
	// 敵座標デバッグ表示
	DrawFormatString(0, 60, 0xffffff, "敵座標(%0.2f,%0.2f,%0.2f)", m_pos.x, m_pos.y, m_pos.z);
	DrawFormatString(0, 80, 0xffffff, "hp:%0.2f", m_hp);
	DrawFormatString(0, 100, 0xffffff, "敵状態:%d", m_currentState);

	// 当たり判定描画
	DrawCapsule3D(m_col.bodyTopPos, m_col.bodyBottomPos, m_colInfo.bodyRadius, 1, 0x0000ff, 0xffffff, false);	// 全身
	DrawCapsule3D(m_col.armStartPos, m_col.armEndPos, m_colInfo.aimRadius, 1, 0xff00ff, 0xffffff, false);		// 腕
	DrawCapsule3D(m_col.legStartPos, m_col.legEndPos, m_colInfo.legRadius, 1, 0xffff00, 0xffffff, false);		// 脚
#endif
}