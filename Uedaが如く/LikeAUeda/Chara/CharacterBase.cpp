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
	m_hp(0.0f),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_moveSpeed(0.0f),
	m_angle(0.0f),
	m_isAttack(false),
	m_modelHandle(-1),
	m_currentPlayAnim(-1),
	m_currentAnimCount(0.0f),
	m_prevPlayAnim(-1),
	m_prevAnimCount(0.0f),
	m_animBlendRate(0.0f)
{
	m_pUIGauge = std::make_shared<UIGauge>();
}


/// <summary>
/// ダメージを受けた際の処理
/// </summary>
void CharacterBase::OnDamage(float damage)
{
	m_hp -= damage;
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
