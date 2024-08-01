#include "DxLib.h"
#include "LoadData.h"
#include "UIGauge.h"
#include "CharacterBase.h"

// �萔
namespace
{
	// �A�j���[�V�������
	constexpr float kAnimBlendMax = 1.0f;	 // �A�j���[�V�����u�����h�̍ő�l
	constexpr float kAnimBlendSpeed = 0.2f;	 // �A�j���[�V�����u�����h�̕ω����x
}

/// <summary>
/// �R���X�g���N�^
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
/// �_���[�W���󂯂��ۂ̏���
/// </summary>
/// <param name="damage">�_���[�W��</param>
void CharacterBase::OnDamage(float damage)
{
	m_hp -= damage;
}


/// <summary>
/// �����蔻��ʒu�X�V
/// </summary>
void CharacterBase::UpdateCol()
{
	// �v���C���[�̌��������Ƃɓ����蔻��̈ʒu�𒲐�����
	MATRIX rotationMatrix = MGetRotY(m_angle);

	// �v���C���[�S�̂̓����蔻��ʒu���X�V
	m_col.bodyTopPos = VAdd(m_pos, (VTransform(VGet(0.0f, m_colInfo.bodyHeight, 0.0f), rotationMatrix)));
	m_col.bodyBottomPos = m_pos;

	// �r�̓����蔻��ʒu���X�V
	m_col.armStartPos = VAdd(m_pos, (VTransform(m_colInfo.armStartPos, rotationMatrix)));
	m_col.armEndPos = VAdd(m_col.armStartPos, (VTransform(m_colInfo.armEndPos, rotationMatrix)));

	// �r�̓����蔻��ʒu���X�V
	m_col.legStartPos = VAdd(m_pos, (VTransform(m_colInfo.legStartPos, rotationMatrix)));
	m_col.legEndPos = VAdd(m_col.legStartPos, (VTransform(m_colInfo.legEndPos, rotationMatrix)));
}


/// <summary>
/// �A�j���[�V�����X�e�[�g���X�V
/// </summary>
/// <param name="prevState">1�O�̃A�j���[�V����</param>
void CharacterBase::UpdateAnimState(CharacterBase::State prevState)
{
	// �U�����͏�Ԃ��X�V���Ȃ�
	if (m_isAttack) return;

	// �ҋ@��Ԃ���
	if (prevState == CharacterBase::State::kFightIdle)
	{
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kRun) PlayAnim(AnimKind::kRun);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kPunch1)PlayAnim(AnimKind::kPunch1);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kKick)	PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kAvoid) PlayAnim(AnimKind::kAvoid);
		// �\���A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// �K�[�h�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// �ړ���Ԃ���
	else if (prevState == CharacterBase::State::kRun)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kPunch1) PlayAnim(AnimKind::kPunch1);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kKick) PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kAvoid) PlayAnim(AnimKind::kAvoid);
		// �\���A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// �K�[�h�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// �p���`���(1�R���{��)����
	else if (prevState == CharacterBase::State::kPunch1)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kRun) PlayAnim(AnimKind::kRun);
		// 2�R���{�ڃA�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kPunch2) PlayAnim(AnimKind::kPunch2);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kKick) PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kAvoid) PlayAnim(AnimKind::kAvoid);
		// �\���A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// �K�[�h�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// �p���`���(2�R���{��)����
	else if (prevState == CharacterBase::State::kPunch2)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kRun) PlayAnim(AnimKind::kRun);
		// 3�R���{�ڃA�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kPunch3) PlayAnim(AnimKind::kPunch3);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kKick) PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kAvoid) PlayAnim(AnimKind::kAvoid);
		// �\���A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// �K�[�h�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// �p���`���(3�R���{��)����
	else if (prevState == CharacterBase::State::kPunch3)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kRun) PlayAnim(AnimKind::kRun);
		// 1�R���{�ڃA�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kPunch1) PlayAnim(AnimKind::kPunch1);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kKick) PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kAvoid) PlayAnim(AnimKind::kAvoid);
		// �\���A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// �K�[�h�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// �L�b�N��Ԃ���
	else if (prevState == CharacterBase::State::kKick)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kRun) PlayAnim(AnimKind::kRun);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kPunch1) PlayAnim(AnimKind::kPunch1);
		// ����A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kAvoid) PlayAnim(AnimKind::kAvoid);
		// �\���A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// �K�[�h�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// �����Ԃ���
	else if (prevState == CharacterBase::State::kAvoid)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kRun) PlayAnim(AnimKind::kRun);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kPunch1) PlayAnim(AnimKind::kPunch1);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kKick) PlayAnim(AnimKind::kKick);
		// �\���A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kFightWalk) PlayAnim(AnimKind::kFightWalk);
		// �K�[�h�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// �\����Ԃ���
	else if (prevState == CharacterBase::State::kFightWalk)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kRun) PlayAnim(AnimKind::kRun);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kPunch1) PlayAnim(AnimKind::kPunch1);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kKick) PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kAvoid) PlayAnim(AnimKind::kAvoid);
		// �K�[�h�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kGuard) PlayAnim(AnimKind::kGuard);
	}
	// �K�[�h��Ԃ���
	else if (prevState == CharacterBase::State::kGuard)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kRun) PlayAnim(AnimKind::kRun);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kPunch1) PlayAnim(AnimKind::kPunch1);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kKick) PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kAvoid) PlayAnim(AnimKind::kAvoid);
		// �\���A�j���[�V�������Đ�
		if (m_currentState == CharacterBase::State::kFightWalk) PlayAnim(AnimKind::kFightWalk);
	}
}


/// <summary>
/// �A�j���[�V�������Đ�����
/// </summary>
/// <param name="PlayAnimIndex">�Đ�����A�j���[�V�������</param>
void CharacterBase::PlayAnim(AnimKind playAnimIndex)
{
	// 1�O�̃A�j���[�V�������A�^�b�`����Ă���ꍇ�폜����
	if (m_prevPlayAnim != -1)
	{
		MV1DetachAnim(m_modelHandle, m_prevPlayAnim);
		m_prevPlayAnim = -1;
	}

	// ���ݍĐ����̃A�j���[�V������1�O�Ɉړ�����
	m_prevPlayAnim = m_currentPlayAnim;
	m_prevAnimCount = m_currentAnimCount;

	// �V���ɃA�j���[�V�������A�^�b�`����
	m_currentPlayAnim = MV1AttachAnim(m_modelHandle, static_cast<int>(playAnimIndex), -1, false);
	m_currentAnimCount = 0.0f;

	// �u�����h����Prev���L���łȂ��ꍇ�A1.0�ɂ���
	if (m_prevPlayAnim == -1)
	{
		m_animBlendRate = kAnimBlendMax;
	}
	else
	{
		m_animBlendRate = 0.0f;
	}
}
