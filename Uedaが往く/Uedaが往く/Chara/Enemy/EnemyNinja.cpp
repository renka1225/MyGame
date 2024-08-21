#include "DxLib.h"
#include "Player.h"
#include "Stage.h"
#include "UIGauge.h"
#include "EffectManager.h"
#include "LoadData.h"
#include "DebugDraw.h"
#include "EnemyNinja.h"

// 定数
namespace
{
	// 敵情報
	const char* const kfileName = "data/Model/Chara/Ninja.mv1";	// 敵のファイル名
	constexpr float kScale = 0.3f;								// 拡大率
	constexpr int kIntervalTime = 180;							// 状態を更新するまでの時間
	const VECTOR kInitPos = VGet(2660, 69.0f, 4280.0f);			// 初期位置
}

/// <summary>
/// コンストラクタ
/// </summary>
EnemyNinja::EnemyNinja()
{
	// キャラクター情報を読み込む
	m_pLoadData = std::make_shared<LoadData>(*this, static_cast<int>(CharaType::kEnemyNinja));
	m_pUIGauge = std::make_shared<UIGauge>(m_status.maxHp);

	m_hp = m_status.maxHp;
	m_pos = kInitPos;
	m_moveSpeed = m_status.maxMoveSpeed;
	m_modelHandle = MV1LoadModel(kfileName);
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	MV1SetPosition(m_modelHandle, kInitPos);
}


/// <summary>
/// デストラクタ
/// </summary>
EnemyNinja::~EnemyNinja()
{
	MV1DeleteModel(m_modelHandle);
}


/// <summary>
///  初期化
/// </summary>
/// <param name="pos">初期位置</param>
void EnemyNinja::Init(VECTOR pos)
{
	m_pos = pos;
	MV1SetPosition(m_modelHandle, m_pos);
	m_pEffect->Init();	// エフェクトの初期化
}


/// <summary>
/// 更新
/// </summary>
/// <param name="player">プレイヤー参照</param>
/// <param name="stage">ステージ参照</param>
void EnemyNinja::Update(Player& player, Stage& stage, SceneStageBase& sceneStage)
{
	// 移動パラメータを設定する
	VECTOR	upMoveVec;		// 上ボタンを入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	leftMoveVec;	// 左ボタンを入力をしたときのプレイヤーの移動方向ベクトル
	VECTOR	moveVec;		// このフレームの移動ベクトル

	// エネミーの状態を更新
	CharacterBase::State prevState = m_currentState;

	// 敵の位置からプレイヤー位置までのベクトルを求める
	m_eToPDirVec = VSub(player.GetPos(), m_pos);

	// 状態を更新する
	m_currentState = UpdateState(player, sceneStage, upMoveVec, leftMoveVec, moveVec);

	// プレイヤーとの当たり判定をチェックする
	player.CheckHitEnemyCol(*this, VGet(m_pos.x, m_pos.y + m_colInfo.bodyHeight, m_pos.z), m_pos, m_colInfo.bodyRadius);

	UpdateAnimState(prevState);		// アニメーション状態を更新
	UpdateAngle();					// 角度を更新
	UpdateGuard();					// ガード状態を更新
	Move(moveVec, player, stage);	// 移動ベクトルを元にエネミーを移動させる
	UpdateAnim();					// アニメーション処理の更新
	UpdateCol();					// 当たり判定の位置更新
	m_pUIGauge->UpdateHpBar();		// HPバーの更新
	m_pEffect->Update();			// エフェクト更新
}


/// <summary>
/// 描画
/// </summary>
void EnemyNinja::Draw()
{
	MV1DrawModel(m_modelHandle);	// 敵モデル描画
	m_pUIGauge->DrawSilhouette(static_cast<int>(CharacterBase::CharaType::kEnemyNinja));	// シルエット描画
	m_pUIGauge->DrawEnemyHp(m_hp);	// HPゲージを表示
	m_pEffect->Draw();				// エフェクト描画

#ifdef _DEBUG
	DebugDraw debug;
	debug.DrawEnemyInfo(m_pos, m_hp, static_cast<int>(m_currentState));
	// 当たり判定描画
	debug.DrawBodyCol(m_col.bodyTopPos, m_col.bodyBottomPos, m_colInfo.bodyRadius); // 全身
	debug.DrawAimCol(m_col.armStartPos, m_col.armEndPos, m_colInfo.aimRadius);		// 腕
	debug.DrawLegCol(m_col.legStartPos, m_col.legEndPos, m_colInfo.legRadius);		// 脚
#endif
}