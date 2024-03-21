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
	m_pModel(pModel)
{
	m_pos.resize(kEnemyNum);
	m_modelHandle = MV1DuplicateModel(m_pModel->GetEnemyHandle());

	// 3D���f���̃T�C�Y������������
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
void Enemy::Init()
{
	// TODO:�G�f�[�^�ǂݍ���
	std::fstream file;
	file.open("data/file/enemy.csv", std::ios::in | std::ios::binary);
	
	if (!file.is_open())	// �t�@�C���ǂݍ��ݎ��s��
	{
		printfDx("�t�@�C���ǂݍ��ݎ��s\n");
	}
	else 					// ������
	{
		// �t�@�C���̒��g����������ɃR�s�[����
		file.read(reinterpret_cast<char*>(&m_pos), sizeof(kEnemyNum));
		file.close();
	}
}

/// <summary>
/// �X�V
/// </summary>
void Enemy::Update()
{
	// TODO:�����z�u
	for (int i = 0; i < m_pos.size(); i++)
	{
		MV1SetPosition(m_modelHandle, m_pos[i]);
	}
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
