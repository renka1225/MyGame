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
	const char* const kfileName = "data/Model/enemy.mv1";	// �G�̃t�@�C����
	constexpr float kScale = 0.25f;							// �g�嗦
	const VECTOR kInitPos = VGet(0.0f, 10.0f, 5.0f);		// �����ʒu

	// �����蔻����
	constexpr float kHitHeight = 50.0f;						// �����蔻��J�v�Z���̍���
	constexpr float kHitRadius = 8.0f;						// �����蔻��J�v�Z���̔��a
	constexpr float kHitAimRadius = 4.0f;					// �r�̓����蔻��J�v�Z���̒���
	constexpr float kHitLegRadius = 5.0f;					// ���̓����蔻��J�v�Z���̒���
	const VECTOR kArmOffset = VGet(0.0f, 0.0f, 0.0f);		// �r�̓����蔻��ʒu
	const VECTOR kArmEndOffset = VGet(0.0f, 0.0f, 0.0f);	// �r�̓����蔻��I���ʒu
	const VECTOR kLegOffset = VGet(0.0f, 0.0f, 0.0f);		// �r�̓����蔻��ʒu
	const VECTOR kLegEndOffset = VGet(0.0f, 0.0f, 0.0f);	// �r�̓����蔻��I���ʒu
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

	// �ړ��x�N�g�������ɃG�l�~�[���ړ�������
	Move(moveVec, player, stage);

	// �p�x���X�V
	UpdateAngle(player);

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
