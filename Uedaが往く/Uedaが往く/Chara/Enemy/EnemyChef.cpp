#include "DxLib.h"
#include "Player.h"
#include "Stage.h"
#include "UIGauge.h"
#include "LoadData.h"
#include "DebugDraw.h"
#include "EnemyChef.h"

// 定数
namespace
{
	// 敵情報
	const char* const kfileName = "data/Model/Chara/Chef.mv1";	// 敵のファイル名
	constexpr float kScale = 0.3f;								// 拡大率
	constexpr int kIntervalTime = 120;							// 状態を更新するまでの時間
	const VECTOR kInitPos = VGet(0.0f, 10.0f, 5.0f);			// 初期位置
}


/// <summary>
/// コンストラクタ
/// </summary>
EnemyChef::EnemyChef()
{
	// キャラクター情報を読み込む
	m_pLoadData = std::make_shared<LoadData>(*this, static_cast<int>(CharaType::kEnemyChef));
	m_pUIGauge = std::make_shared<UIGauge>(m_status.maxHp);

	m_hp = m_status.maxHp;
	m_pos = kInitPos;
	m_moveSpeed = m_status.maxMoveSpeed;
	m_modelHandle = MV1LoadModel(kfileName);
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
}


/// <summary>
/// デストラクタ
/// </summary>
EnemyChef::~EnemyChef()
{
	MV1DeleteModel(m_modelHandle);
}


/// <summary>
/// 初期化
/// </summary>
void EnemyChef::Init()
{
	MV1SetPosition(m_modelHandle, kInitPos);
}


/// <summary>
/// 更新
/// </summary>
/// <param name="player">プレイヤー参照</param>
/// <param name="stage">ステージ参照</param>
void EnemyChef::Update(Player& player, Stage& stage)
{
	// 移動パラメータを設定する
	VECTOR	upMoveVec;		// 上ボタンを入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	leftMoveVec;	// 左ボタンを入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	moveVec;		// このフレームの移動ベクトル

	// エネミーの状態を更新
	CharacterBase::State prevState = m_currentState;

	// 敵の位置からプレイヤー位置までのベクトルを求める
	m_eToPDirVec = VSub(player.GetPos(), m_pos);

	// 次の行動を決める
	DecideNextAction();
	m_intervalTime--;

	// 移動処理
	m_currentState = UpdateMoveParameter(player, upMoveVec, leftMoveVec, moveVec);

	// プレイヤーとの当たり判定をチェックする
	player.CheckHitEnemyCol(*this, VGet(m_pos.x, m_pos.y + m_colInfo.bodyHeight, m_pos.z), m_pos, m_colInfo.bodyRadius);

	// アニメーション状態を更新
	UpdateAnimState(prevState);

	// 角度を更新
	UpdateAngle();

	// 移動ベクトルを元にエネミーを移動させる
	Move(moveVec, player, stage);

	// アニメーション処理の更新
	UpdateAnim();

	// 当たり判定の位置更新
	UpdateCol();

	// HPバーの更新
	m_pUIGauge->UpdateHpBar();
}


/// <summary>
/// 描画
/// </summary>
void EnemyChef::Draw()
{
	// 敵モデル描画
	MV1DrawModel(m_modelHandle);

	// HPゲージを表示
	m_pUIGauge->DrawEnemyHp(m_hp);

#ifdef _DEBUG
	DebugDraw debug;
	debug.DrawEnemyInfo(m_pos, m_hp, static_cast<int>(m_currentState));
	// 当たり判定描画
	debug.DrawBodyCol(m_col.bodyTopPos, m_col.bodyBottomPos, m_colInfo.bodyRadius); // 全身
	debug.DrawAimCol(m_col.armStartPos, m_col.armEndPos, m_colInfo.aimRadius);		// 腕
	debug.DrawLegCol(m_col.legStartPos, m_col.legEndPos, m_colInfo.legRadius);		// 脚
#endif
}


/// <summary>
/// ダメージを受けた際の処理
/// </summary>
/// <param name="damage">ダメージ量</param>
void EnemyChef::OnDamage(float damage)
{
	m_hp -= damage;
	// HPバーを更新
	if (damage > 0.0f)
	{
		m_pUIGauge->OnDamage(damage);
	}
}


/// <summary>
/// 次の行動を決める
/// </summary>
void EnemyChef::DecideNextAction()
{
	if (m_intervalTime > 0) return;

	// 攻撃中かつ移動中でない場合
	if (!m_isAttack && m_currentState != CharacterBase::State::kRun)
	{
		//// 確率で攻撃を行う
		//int randNum = GetRand(m_enemyInfo.maxProb);

		//// キック攻撃
		//if (randNum <= m_enemyInfo.kickProb)
		//{
		//	kick();
		//}
		//// パンチ攻撃
		//if (randNum <= m_enemyInfo.kickProb + m_enemyInfo.punchProb)
		//{
		//	Punch();
		//}

		m_intervalTime = kIntervalTime;
	}
}
