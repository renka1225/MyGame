#include "DxLib.h"
#include "Player.h"
#include "Stage.h"
#include "UIGauge.h"
#include "LoadData.h"
#include "DebugDraw.h"
#include "EnemyChef.h"

// �萔
namespace
{
	// �G���
	const char* const kfileName = "data/Model/Chara/Chef.mv1";	// �G�̃t�@�C����
	constexpr float kScale = 0.3f;								// �g�嗦
	constexpr int kIntervalTime = 120;							// ��Ԃ��X�V����܂ł̎���
	const VECTOR kInitPos = VGet(0.0f, 10.0f, 5.0f);			// �����ʒu
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyChef::EnemyChef()
{
	// �L�����N�^�[����ǂݍ���
	m_pLoadData = std::make_shared<LoadData>(*this, static_cast<int>(CharaType::kEnemyChef));
	m_pUIGauge = std::make_shared<UIGauge>(m_status.maxHp);

	m_hp = m_status.maxHp;
	m_pos = kInitPos;
	m_moveSpeed = m_status.maxMoveSpeed;
	m_modelHandle = MV1LoadModel(kfileName);
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyChef::~EnemyChef()
{
	MV1DeleteModel(m_modelHandle);
}


/// <summary>
/// ������
/// </summary>
void EnemyChef::Init()
{
	MV1SetPosition(m_modelHandle, kInitPos);
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="player">�v���C���[�Q��</param>
/// <param name="stage">�X�e�[�W�Q��</param>
void EnemyChef::Update(Player& player, Stage& stage)
{
	// �ړ��p�����[�^��ݒ肷��
	VECTOR	upMoveVec;		// ��{�^������͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
	VECTOR	leftMoveVec;	// ���{�^������͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
	VECTOR	moveVec;		// ���̃t���[���̈ړ��x�N�g��

	// �G�l�~�[�̏�Ԃ��X�V
	CharacterBase::State prevState = m_currentState;

	// �G�̈ʒu����v���C���[�ʒu�܂ł̃x�N�g�������߂�
	m_eToPDirVec = VSub(player.GetPos(), m_pos);

	// ���̍s�������߂�
	DecideNextAction();
	m_intervalTime--;

	// �ړ�����
	m_currentState = UpdateMoveParameter(player, upMoveVec, leftMoveVec, moveVec);

	// �v���C���[�Ƃ̓����蔻����`�F�b�N����
	player.CheckHitEnemyCol(*this, VGet(m_pos.x, m_pos.y + m_colInfo.bodyHeight, m_pos.z), m_pos, m_colInfo.bodyRadius);

	// �A�j���[�V������Ԃ��X�V
	UpdateAnimState(prevState);

	// �p�x���X�V
	UpdateAngle();

	// �ړ��x�N�g�������ɃG�l�~�[���ړ�������
	Move(moveVec, player, stage);

	// �A�j���[�V���������̍X�V
	UpdateAnim();

	// �����蔻��̈ʒu�X�V
	UpdateCol();

	// HP�o�[�̍X�V
	m_pUIGauge->UpdateHpBar();
}


/// <summary>
/// �`��
/// </summary>
void EnemyChef::Draw()
{
	// �G���f���`��
	MV1DrawModel(m_modelHandle);

	// HP�Q�[�W��\��
	m_pUIGauge->DrawEnemyHp(m_hp);

#ifdef _DEBUG
	DebugDraw debug;
	debug.DrawEnemyInfo(m_pos, m_hp, static_cast<int>(m_currentState));
	// �����蔻��`��
	debug.DrawBodyCol(m_col.bodyTopPos, m_col.bodyBottomPos, m_colInfo.bodyRadius); // �S�g
	debug.DrawAimCol(m_col.armStartPos, m_col.armEndPos, m_colInfo.aimRadius);		// �r
	debug.DrawLegCol(m_col.legStartPos, m_col.legEndPos, m_colInfo.legRadius);		// �r
#endif
}


/// <summary>
/// �_���[�W���󂯂��ۂ̏���
/// </summary>
/// <param name="damage">�_���[�W��</param>
void EnemyChef::OnDamage(float damage)
{
	m_hp -= damage;
	// HP�o�[���X�V
	if (damage > 0.0f)
	{
		m_pUIGauge->OnDamage(damage);
	}
}


/// <summary>
/// ���̍s�������߂�
/// </summary>
void EnemyChef::DecideNextAction()
{
	if (m_intervalTime > 0) return;

	// �U�������ړ����łȂ��ꍇ
	if (!m_isAttack && m_currentState != CharacterBase::State::kRun)
	{
		//// �m���ōU�����s��
		//int randNum = GetRand(m_enemyInfo.maxProb);

		//// �L�b�N�U��
		//if (randNum <= m_enemyInfo.kickProb)
		//{
		//	kick();
		//}
		//// �p���`�U��
		//if (randNum <= m_enemyInfo.kickProb + m_enemyInfo.punchProb)
		//{
		//	Punch();
		//}

		m_intervalTime = kIntervalTime;
	}
}
