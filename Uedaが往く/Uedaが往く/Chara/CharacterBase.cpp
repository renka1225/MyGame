#include "DxLib.h"
#include "LoadData.h"
#include "UIGauge.h"
#include "CharacterBase.h"

// 定数
namespace
{
	// アニメーション情報
	constexpr float kAnimBlendMax = 1.0f;	 // アニメーションブレンドの最大値
	constexpr float kAnimBlendSpeed = 0.2f;	 // アニメーションブレンドの変化速度
}

/// <summary>
/// コンストラクタ
/// </summary>
CharacterBase::CharacterBase():
	m_animSpeed{0.0f},
	m_status{0.0f},
	m_colInfo{0.0f},
	m_hp(0.0f),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_moveSpeed(0.0f),
	m_angle(0.0f),
	m_isAttack(false),
	m_isGuard(false),
	m_modelHandle(-1),
	m_currentPlayAnim(-1),
	m_currentAnimCount(0.0f),
	m_prevPlayAnim(-1),
	m_prevAnimCount(0.0f),
	m_animBlendRate(0.0f)
{
}


/// <summary>
/// ダメージを受けた際の処理
/// </summary>
/// <param name="damage">ダメージ量</param>
void CharacterBase::OnDamage(float damage)
{
	m_hp -= damage;
}


/// <summary>
/// 当たり判定位置更新
/// </summary>
void CharacterBase::UpdateCol()
{
	// プレイヤーの向きをもとに当たり判定の位置を調整する
	MATRIX rotationMatrix = MGetRotY(m_angle);

	// プレイヤー全体の当たり判定位置を更新
	m_col.bodyTopPos = VAdd(m_pos, (VTransform(VGet(0.0f, m_colInfo.bodyHeight, 0.0f), rotationMatrix)));
	m_col.bodyBottomPos = m_pos;

	// 腕の当たり判定位置を更新
	m_col.armStartPos = VAdd(m_pos, (VTransform(m_colInfo.armStartPos, rotationMatrix)));
	m_col.armEndPos = VAdd(m_col.armStartPos, (VTransform(m_colInfo.armEndPos, rotationMatrix)));

	// 脚の当たり判定位置を更新
	m_col.legStartPos = VAdd(m_pos, (VTransform(m_colInfo.legStartPos, rotationMatrix)));
	m_col.legEndPos = VAdd(m_col.legStartPos, (VTransform(m_colInfo.legEndPos, rotationMatrix)));
}


/// <summary>
/// アニメーションステートを更新
/// </summary>
/// <param name="prevState">1つ前のアニメーション</param>
void CharacterBase::UpdateAnimState(CharacterBase::State prevState)
{
	// 攻撃中は状態を更新しない
	if (m_isAttack) return;

	// 待機状態から
	if (prevState == CharacterBase::State::kFightIdle)
	{
		// 移動アニメーションを再生
		if (m_currentState == CharacterBase::State::kRun) PlayAnim(AnimKind::kRun);
		// パンチアニメーションを再生
		if (m_currentState == CharacterBase::State::kPunch1)PlayAnim(AnimKind::kPunch1);
		// キックアニメーションを再生
		if (m_currentState == CharacterBase::State::kKick)	PlayAnim(AnimKind::kKick);
		// 回避アニメーションを再生
		if (m_currentState == CharacterBase::State::kAvoid) PlayAnim(AnimKind::kAvoid);
		// 構えアニメーションを再生
		if (m_currentState == CharacterBase::State::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// ガードアニメーションを再生
		if (m_currentState == CharacterBase::State::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// 移動状態から
	else if (prevState == CharacterBase::State::kRun)
	{
		// 待機アニメーションを再生
		if (m_currentState == CharacterBase::State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// パンチアニメーションを再生
		if (m_currentState == CharacterBase::State::kPunch1) PlayAnim(AnimKind::kPunch1);
		// キックアニメーションを再生
		if (m_currentState == CharacterBase::State::kKick) PlayAnim(AnimKind::kKick);
		// 回避アニメーションを再生
		if (m_currentState == CharacterBase::State::kAvoid) PlayAnim(AnimKind::kAvoid);
		// 構えアニメーションを再生
		if (m_currentState == CharacterBase::State::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// ガードアニメーションを再生
		if (m_currentState == CharacterBase::State::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// パンチ状態(1コンボ目)から
	else if (prevState == CharacterBase::State::kPunch1)
	{
		// 待機アニメーションを再生
		if (m_currentState == CharacterBase::State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// 移動アニメーションを再生
		if (m_currentState == CharacterBase::State::kRun) PlayAnim(AnimKind::kRun);
		// 2コンボ目アニメーションを再生
		if (m_currentState == CharacterBase::State::kPunch2) PlayAnim(AnimKind::kPunch2);
		// キックアニメーションを再生
		if (m_currentState == CharacterBase::State::kKick) PlayAnim(AnimKind::kKick);
		// 回避アニメーションを再生
		if (m_currentState == CharacterBase::State::kAvoid) PlayAnim(AnimKind::kAvoid);
		// 構えアニメーションを再生
		if (m_currentState == CharacterBase::State::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// ガードアニメーションを再生
		if (m_currentState == CharacterBase::State::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// パンチ状態(2コンボ目)から
	else if (prevState == CharacterBase::State::kPunch2)
	{
		// 待機アニメーションを再生
		if (m_currentState == CharacterBase::State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// 移動アニメーションを再生
		if (m_currentState == CharacterBase::State::kRun) PlayAnim(AnimKind::kRun);
		// 3コンボ目アニメーションを再生
		if (m_currentState == CharacterBase::State::kPunch3) PlayAnim(AnimKind::kPunch3);
		// キックアニメーションを再生
		if (m_currentState == CharacterBase::State::kKick) PlayAnim(AnimKind::kKick);
		// 回避アニメーションを再生
		if (m_currentState == CharacterBase::State::kAvoid) PlayAnim(AnimKind::kAvoid);
		// 構えアニメーションを再生
		if (m_currentState == CharacterBase::State::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// ガードアニメーションを再生
		if (m_currentState == CharacterBase::State::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// パンチ状態(3コンボ目)から
	else if (prevState == CharacterBase::State::kPunch3)
	{
		// 待機アニメーションを再生
		if (m_currentState == CharacterBase::State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// 移動アニメーションを再生
		if (m_currentState == CharacterBase::State::kRun) PlayAnim(AnimKind::kRun);
		// 1コンボ目アニメーションを再生
		if (m_currentState == CharacterBase::State::kPunch1) PlayAnim(AnimKind::kPunch1);
		// キックアニメーションを再生
		if (m_currentState == CharacterBase::State::kKick) PlayAnim(AnimKind::kKick);
		// 回避アニメーションを再生
		if (m_currentState == CharacterBase::State::kAvoid) PlayAnim(AnimKind::kAvoid);
		// 構えアニメーションを再生
		if (m_currentState == CharacterBase::State::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// ガードアニメーションを再生
		if (m_currentState == CharacterBase::State::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// キック状態から
	else if (prevState == CharacterBase::State::kKick)
	{
		// 待機アニメーションを再生
		if (m_currentState == CharacterBase::State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// 移動アニメーションを再生
		if (m_currentState == CharacterBase::State::kRun) PlayAnim(AnimKind::kRun);
		// パンチアニメーションを再生
		if (m_currentState == CharacterBase::State::kPunch1) PlayAnim(AnimKind::kPunch1);
		// 回避アニメーションを再生
		if (m_currentState == CharacterBase::State::kAvoid) PlayAnim(AnimKind::kAvoid);
		// 構えアニメーションを再生
		if (m_currentState == CharacterBase::State::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// ガードアニメーションを再生
		if (m_currentState == CharacterBase::State::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// 回避状態から
	else if (prevState == CharacterBase::State::kAvoid)
	{
		// 待機アニメーションを再生
		if (m_currentState == CharacterBase::State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// 移動アニメーションを再生
		if (m_currentState == CharacterBase::State::kRun) PlayAnim(AnimKind::kRun);
		// パンチアニメーションを再生
		if (m_currentState == CharacterBase::State::kPunch1) PlayAnim(AnimKind::kPunch1);
		// キックアニメーションを再生
		if (m_currentState == CharacterBase::State::kKick) PlayAnim(AnimKind::kKick);
		// 構えアニメーションを再生
		if (m_currentState == CharacterBase::State::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// ガードアニメーションを再生
		if (m_currentState == CharacterBase::State::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// 構え状態から
	else if (prevState == CharacterBase::State::kFightWalk)
	{
		// 待機アニメーションを再生
		if (m_currentState == CharacterBase::State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// 移動アニメーションを再生
		if (m_currentState == CharacterBase::State::kRun) PlayAnim(AnimKind::kRun);
		// パンチアニメーションを再生
		if (m_currentState == CharacterBase::State::kPunch1) PlayAnim(AnimKind::kPunch1);
		// キックアニメーションを再生
		if (m_currentState == CharacterBase::State::kKick) PlayAnim(AnimKind::kKick);
		// 回避アニメーションを再生
		if (m_currentState == CharacterBase::State::kAvoid) PlayAnim(AnimKind::kAvoid);
		// ガードアニメーションを再生
		if (m_currentState == CharacterBase::State::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// ガード状態から
	else if (prevState == CharacterBase::State::kGuard)
	{
		// 待機アニメーションを再生
		if (m_currentState == CharacterBase::State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// 移動アニメーションを再生
		if (m_currentState == CharacterBase::State::kRun) PlayAnim(AnimKind::kRun);
		// パンチアニメーションを再生
		if (m_currentState == CharacterBase::State::kPunch1) PlayAnim(AnimKind::kPunch1);
		// キックアニメーションを再生
		if (m_currentState == CharacterBase::State::kKick) PlayAnim(AnimKind::kKick);
		// 回避アニメーションを再生
		if (m_currentState == CharacterBase::State::kAvoid) PlayAnim(AnimKind::kAvoid);
		// 構えアニメーションを再生
		if (m_currentState == CharacterBase::State::kFightWalk) PlayAnim(AnimKind::kFightWalk);
	}
}


/// <summary>
/// アニメーションを再生する
/// </summary>
/// <param name="PlayAnimIndex">再生するアニメーション状態</param>
void CharacterBase::PlayAnim(AnimKind playAnimIndex)
{
	// 1つ前のアニメーションがアタッチされている場合削除する
	if (m_prevPlayAnim != -1)
	{
		MV1DetachAnim(m_modelHandle, m_prevPlayAnim);
		m_prevPlayAnim = -1;
	}

	// 現在再生中のアニメーションを1つ前に移動する
	m_prevPlayAnim = m_currentPlayAnim;
	m_prevAnimCount = m_currentAnimCount;

	// 新たにアニメーションをアタッチする
	m_currentPlayAnim = MV1AttachAnim(m_modelHandle, static_cast<int>(playAnimIndex), -1, false);
	m_currentAnimCount = 0.0f;

	// ブレンド率はPrevが有効でない場合、1.0にする
	if (m_prevPlayAnim == -1)
	{
		m_animBlendRate = kAnimBlendMax;
	}
	else
	{
		m_animBlendRate = 0.0f;
	}
}
