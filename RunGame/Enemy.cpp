#include "Enemy.h"
#include "ManagerModel.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pModel">3D���f��</param>
Enemy::Enemy(std::shared_ptr<ManagerModel> pModel) :
	m_pModel(pModel),
	m_pos(VGet(0.0f, 0.0f, 0.0f))
{
	m_modelHandle = MV1DuplicateModel(m_pModel->GetEnemyHandle());

	// 3D���f���̏k��
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	// 3D���f����Y�������ɉ�]
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, kDirY, 0.0f));
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
Enemy::~Enemy()
{
	MV1DeleteModel(m_modelHandle);
}


/// <summary>
/// ������
/// </summary>
void Enemy::Init(VECTOR pos)
{
	m_pos = pos;
}

/// <summary>
/// �X�V
/// </summary>
void Enemy::Update()
{
	// �G�z�u
	MV1SetPosition(m_modelHandle, m_pos);
	
}


/// <summary>
/// �`��
/// </summary>
void Enemy::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(m_modelHandle);
}


/// <summary>
/// �I��
/// </summary>
void Enemy::End()
{
}
