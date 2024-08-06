#include "DxLib.h"
#include "Player.h"
#include "Stage.h"
#include "UIGauge.h"
#include "LoadData.h"
#include "DebugDraw.h"
#include "EnemyAbe.h"

// �萔
namespace
{
	// �G���
	const char* const kfileName = "data/Model/Chara/Abe.mv1";	// �G�̃t�@�C����
	constexpr float kScale = 0.3f;								// �g�嗦
	constexpr int kIntervalTime = 120;							// ��Ԃ��X�V����܂ł̎���
	const VECTOR kInitPos = VGet(2800.0f, 69.0f, 4370.0f);		// �����ʒu
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyAbe::EnemyAbe()
{
	// �L�����N�^�[����ǂݍ���
	m_pLoadData = std::make_shared<LoadData>(*this, static_cast<int>(CharaType::kEnemyAbe));
	m_pUIGauge = std::make_shared<UIGauge>(m_status.maxHp);

	m_hp = m_status.maxHp;
	m_pos = kInitPos;
	m_moveSpeed = m_status.maxMoveSpeed;
	m_modelHandle = MV1LoadModel(kfileName);
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	MV1SetPosition(m_modelHandle, kInitPos);
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyAbe::~EnemyAbe()
{
	MV1DeleteModel(m_modelHandle);
}


/// <summary>
/// ������
/// </summary>
void EnemyAbe::Init()
{
}


/// <summary>
/// �X�V
/// </summary>
/// <param name="player">�v���C���[�Q��</param>
/// <param name="stage">�X�e�[�W�Q��</param>
void EnemyAbe::Update(Player& player, Stage& stage)
{
	// �ړ��p�����[�^��ݒ肷��
	VECTOR	upMoveVec;		// ��{�^������͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
	VECTOR	leftMoveVec;	// ���{�^������͂������Ƃ��̃v���C���[�̈ړ������x�N�g��
	VECTOR	moveVec;		// ���̃t���[���̈ړ��x�N�g��

	// �G�l�~�[�̏�Ԃ��X�V
	CharacterBase::State prevState = m_currentState;

	// �G�̈ʒu����v���C���[�ʒu�܂ł̃x�N�g�������߂�
	m_eToPDirVec = VSub(player.GetPos(), m_pos);

	// ��Ԃ��X�V����
	m_intervalTime--;
	m_currentState = UpdateState(player, upMoveVec, leftMoveVec, moveVec);

	// �v���C���[�Ƃ̓����蔻����`�F�b�N����
	player.CheckHitEnemyCol(*this, VGet(m_pos.x, m_pos.y + m_colInfo.bodyHeight, m_pos.z), m_pos, m_colInfo.bodyRadius);

	UpdateAnimState(prevState);		// �A�j���[�V������Ԃ��X�V
	UpdateAngle();					// �p�x���X�V
	UpdateGuard();					// �K�[�h��Ԃ��X�V
	Move(moveVec, player, stage);	// �ړ��x�N�g�������ɃG�l�~�[���ړ�������
	UpdateAnim();					// �A�j���[�V���������̍X�V
	UpdateCol();					// �����蔻��̈ʒu�X�V
	m_pUIGauge->UpdateHpBar();		// HP�o�[�̍X�V
}


/// <summary>
/// �`��
/// </summary>
void EnemyAbe::Draw()
{
	MV1DrawModel(m_modelHandle);	// �G���f���`��
	m_pUIGauge->DrawSilhouette(static_cast<int>(CharacterBase::CharaType::kEnemyAbe));	// �V���G�b�g�`��
	m_pUIGauge->DrawEnemyHp(m_hp);	// HP�Q�[�W��\��

#ifdef _DEBUG
	DebugDraw debug;
	debug.DrawEnemyInfo(m_pos, m_hp, static_cast<int>(m_currentState));
	// �����蔻��`��
	debug.DrawBodyCol(m_col.bodyTopPos, m_col.bodyBottomPos, m_colInfo.bodyRadius); // �S�g
	debug.DrawAimCol(m_col.armStartPos, m_col.armEndPos, m_colInfo.aimRadius);		// �r
	debug.DrawLegCol(m_col.legStartPos, m_col.legEndPos, m_colInfo.legRadius);		// �r
#endif
}