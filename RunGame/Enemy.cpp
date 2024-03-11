#include "Enemy.h"
#include "ManagerModel.h"

/// <summary>
/// �萔
/// </summary>
namespace
{
	// �ړ���
	constexpr float kMoveX = -1.0f;
	// �g�嗦
	constexpr float kScale = 0.25f;
	// Y�������̌���
	constexpr float kDirY = 180.0f * DX_PI_F / 180.0f;
}

Enemy::Enemy():
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_move(VGet(kMoveX, 0.0f, 0.0f))
{
	m_pModel = std::make_shared<ManagerModel>();

	// 3D���f���̃T�C�Y������������
	MV1SetScale(m_pModel->GetEnemyHandle(), VGet(kScale, kScale, kScale));
	// 3D���f����Y�������ɉ�]
	MV1SetRotationXYZ(m_pModel->GetEnemyHandle(), VGet(0.0f, kDirY, 0.0f));
}


Enemy::~Enemy()
{
}


/// <summary>
/// ������
/// </summary>
void Enemy::Init()
{
}


/// <summary>
/// �X�V
/// </summary>
void Enemy::Update()
{
	// �ʒu�X�V
	//m_pos = VAdd(m_pos, m_move);
	MV1SetPosition(m_pModel->GetEnemyHandle(), m_pos);
}


/// <summary>
/// �`��
/// </summary>
void Enemy::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(m_pModel->GetEnemyHandle());
}


/// <summary>
/// �I��
/// </summary>
void Enemy::End()
{
}
