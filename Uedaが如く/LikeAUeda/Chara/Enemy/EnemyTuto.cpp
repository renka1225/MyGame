#include "DxLib.h"
#include "Player.h"
#include "Stage.h"
#include "UIGauge.h"
#include "LoadData.h"
#include "EnemyTuto.h"

// �萔
namespace
{
	// �G���
	const char* const kfileName = "data/Model/enemyTuto.mv1";	// �G�̃t�@�C����
	constexpr float kScale = 0.3f;							// �g�嗦
	const VECTOR kInitPos = VGet(0.0f, 10.0f, 5.0f);		// �����ʒu

	// �����蔻����
	constexpr float kHitHeight = 45.0f;						// �����蔻��J�v�Z���̍���
	constexpr float kHitRadius = 8.0f;						// �����蔻��J�v�Z���̔��a
	constexpr float kHitAimRadius = 4.0f;					// �r�̓����蔻��J�v�Z���̒���
	constexpr float kHitLegRadius = 5.0f;					// ���̓����蔻��J�v�Z���̒���
	const VECTOR kArmOffset = VGet(0.0f, 0.0f, 0.0f);		// �r�̓����蔻��ʒu
	const VECTOR kArmEndOffset = VGet(0.0f, 0.0f, 0.0f);	// �r�̓����蔻��I���ʒu
	const VECTOR kLegOffset = VGet(0.0f, 0.0f, 0.0f);		// �r�̓����蔻��ʒu
	const VECTOR kLegEndOffset = VGet(0.0f, 0.0f, 0.0f);	// �r�̓����蔻��I���ʒu

	// �A�j���[�V�������
	constexpr float kAnimBlendMax = 1.0f;	 // �A�j���[�V�����u�����h�̍ő�l
	constexpr float kAnimBlendSpeed = 0.2f;	 // �A�j���[�V�����u�����h�̕ω����x
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyTuto::EnemyTuto()
{
	// �L�����N�^�[����ǂݍ���
	m_pLoadData = std::make_shared<LoadData>(*this, static_cast<int>(CharaType::kEnemyTuto));

	m_hp = m_status.maxHp;
	m_pos = kInitPos;
	m_moveSpeed = m_status.maxMoveSpeed;
	m_modelHandle = MV1LoadModel(kfileName);
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyTuto::~EnemyTuto()
{
	MV1DeleteModel(m_modelHandle);
}


/// <summary>
/// ������
/// </summary>
void EnemyTuto::Init()
{
	MV1SetPosition(m_modelHandle, kInitPos);
}


/// <summary>
/// �X�V
/// </summary>
void EnemyTuto::Update(Player& player, Stage& stage)
{
	// �ړ��p�����[�^��ݒ肷��
	VECTOR	upMoveVec;		// ��{�^������͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
	VECTOR	leftMoveVec;	// ���{�^������͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
	VECTOR	moveVec;		// ���̃t���[���̈ړ��x�N�g��

	// �G�l�~�[�̏�Ԃ��X�V
	EnemyState prevState = m_currentState;

	// �ړ�����
	m_currentState = UpdateMoveParameter(player, upMoveVec, leftMoveVec, moveVec);

	// �v���C���[�Ƃ̓����蔻����`�F�b�N����
	player.CheckHitEnemyCol(*this, VGet(m_pos.x, m_pos.y + kHitHeight, m_pos.z), m_pos, kHitRadius);

	// �A�j���[�V������Ԃ��X�V
	UpdateAnimState(prevState);

	// �p�x���X�V
	UpdateAngle(player);

	// �ړ��x�N�g�������ɃG�l�~�[���ړ�������
	Move(moveVec, player, stage);

	// �A�j���[�V���������̍X�V
	UpdateAnim();

	// �����蔻��̈ʒu�X�V
	UpdateCol();
}


/// <summary>
/// �`��
/// </summary>
void EnemyTuto::Draw()
{
	// �G���f���`��
	MV1DrawModel(m_modelHandle);

	// HP�Q�[�W��\��
	m_pUIGauge->DrawEnemyHp(m_hp, m_status.maxHp);

#ifdef _DEBUG
	// �G���W�f�o�b�O�\��
	DrawFormatString(0, 60, 0xffffff, "�G���W(%0.2f,%0.2f,%0.2f)", m_pos.x, m_pos.y, m_pos.z);
	DrawFormatString(0, 80, 0xffffff, "hp:%0.2f", m_hp);
	DrawFormatString(0, 100, 0xffffff, "�G���:%d", m_currentState);

	// �����蔻��`��
	DrawCapsule3D(m_col.hitTopPos, m_col.hitBottomPos, kHitRadius, 1, 0x0000ff, 0xffffff, false);	// �S�g
	DrawCapsule3D(m_col.armStartPos, m_col.armEndPos, kHitAimRadius, 1, 0xff00ff, 0xffffff, false);	// �r
	DrawCapsule3D(m_col.legStartPos, m_col.legEndPos, kHitLegRadius, 1, 0xffff00, 0xffffff, false);	// �r
#endif

}


/// <summary>
/// �����蔻��ʒu�̍X�V
/// </summary>
void EnemyTuto::UpdateCol()
{
	// �v���C���[�̌��������Ƃɓ����蔻��̈ʒu�𒲐�����
	MATRIX rotationMatrix = MGetRotY(m_angle);

	// �v���C���[�S�̂̓����蔻��ʒu���X�V
	m_col.hitTopPos = VAdd(m_pos, (VTransform(VGet(0.0f, kHitHeight, 0.0f), rotationMatrix)));
	m_col.hitBottomPos = m_pos;

	// �r�̓����蔻��ʒu���X�V
	m_col.armStartPos = VAdd(m_pos, (VTransform(kArmOffset, rotationMatrix)));
	m_col.armEndPos = VAdd(m_col.armStartPos, (VTransform(kArmEndOffset, rotationMatrix)));

	// �r�̓����蔻��ʒu���X�V
	m_col.legStartPos = VAdd(m_pos, (VTransform(kLegOffset, rotationMatrix)));
	m_col.legEndPos = VAdd(m_col.legStartPos, (VTransform(kLegEndOffset, rotationMatrix)));
}


/// <summary>
/// �A�j���[�V�����X�e�[�g�̍X�V
/// </summary>
/// <param name="prevState"></param>
void EnemyTuto::UpdateAnimState(EnemyState prevState)
{
	// �U�����͏�Ԃ��X�V���Ȃ�
	if (m_isAttack) return;

	// �ҋ@��Ԃ���
	if (prevState == EnemyState::kFightIdle)
	{
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kRun) PlayAnim(AnimKind::kRun);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kPunch)PlayAnim(AnimKind::kPunch);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kKick)	PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kAvoid) PlayAnim(AnimKind::kAvoid);
	}
	// �ړ���Ԃ���
	else if (prevState == EnemyState::kRun)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kPunch) PlayAnim(AnimKind::kPunch);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kKick) PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kAvoid) PlayAnim(AnimKind::kAvoid);
	}
	// �p���`��Ԃ���
	else if (prevState == EnemyState::kPunch)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kRun) PlayAnim(AnimKind::kRun);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kKick) PlayAnim(AnimKind::kKick);
		// ����A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kAvoid) PlayAnim(AnimKind::kAvoid);
	}
	// �L�b�N��Ԃ���
	else if (prevState == EnemyState::kKick)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kRun) PlayAnim(AnimKind::kRun);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kPunch) PlayAnim(AnimKind::kPunch);
		// ����A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kAvoid) PlayAnim(AnimKind::kAvoid);
	}
	// �����Ԃ���
	else if (prevState == EnemyState::kAvoid)
	{
		// �ҋ@�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kFightIdle) PlayAnim(AnimKind::kFightIdle);
		// �ړ��A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kRun) PlayAnim(AnimKind::kRun);
		// �p���`�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kPunch) PlayAnim(AnimKind::kPunch);
		// �L�b�N�A�j���[�V�������Đ�
		if (m_currentState == EnemyState::kKick) PlayAnim(AnimKind::kKick);
	}
}


/// <summary>
/// �A�j���[�V��������
/// </summary>
void EnemyTuto::UpdateAnim()
{
	float animTotalTime; // �Đ����̃A�j���[�V��������

	// �u�����h����1�ȉ��̏ꍇ
	if (m_animBlendRate < kAnimBlendMax)
	{
		m_animBlendRate += kAnimBlendSpeed;
		if (m_animBlendRate >= kAnimBlendMax)
		{
			m_animBlendRate = kAnimBlendMax;
		}
	}

	// ���ݍĐ����̃A�j���[�V�����̏���
	if (m_currentPlayAnim != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_currentPlayAnim);
		if (m_isAttack)
		{
			m_currentAnimCount += m_animSpeed.punch;
		}
		else
		{
			m_currentAnimCount += m_animSpeed.fightIdle;
		}

		// �A�j���[�V�����̍Đ����Ԃ����[�v
		if (m_currentAnimCount > animTotalTime)
		{
			// �U���A�j���[�V�������I��������ҋ@��ԂɈڍs
			if (m_isAttack)
			{
				m_isAttack = false;
				m_currentState = EnemyState::kFightIdle;
				PlayAnim(AnimKind::kFightIdle);
			}

			m_currentAnimCount = static_cast<float>(fmod(m_currentAnimCount, animTotalTime));
		}

		// �Đ����Ԃ��X�V
		MV1SetAttachAnimTime(m_modelHandle, m_currentPlayAnim, m_currentAnimCount);
		// �A�j���[�V�����̃u�����h����ݒ肷��
		MV1SetAttachAnimBlendRate(m_modelHandle, m_currentPlayAnim, m_animBlendRate);


	}

	// 1�O�ɍĐ����Ă����A�j���[�V�����̏���
	if (m_prevPlayAnim != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_prevPlayAnim);
		if (m_isAttack)
		{
			m_prevAnimCount += m_animSpeed.punch;
		}
		else
		{
			m_prevAnimCount += m_animSpeed.fightIdle;
		}

		// �A�j���[�V�����̍Đ����Ԃ����[�v
		if (m_prevPlayAnim > animTotalTime)
		{
			m_prevAnimCount = static_cast<float>(fmod(m_prevAnimCount, animTotalTime));
		}

		// �Đ����Ԃ��X�V
		MV1SetAttachAnimTime(m_modelHandle, m_prevPlayAnim, m_prevAnimCount);
		// �A�j���[�V�����̃u�����h����ݒ肷��
		MV1SetAttachAnimBlendRate(m_modelHandle, m_prevPlayAnim, kAnimBlendMax - m_animBlendRate);
	}
}
