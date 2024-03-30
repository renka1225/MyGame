#include "Enemy.h"
#include "ManagerModel.h"
#include "Game/Game.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="pModel">3D���f��</param>
Enemy::Enemy(std::shared_ptr<ManagerModel> pModel) :
	m_pModel(pModel),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_isExist(false)
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
	//  �G�̍��W���X�N���[�����W�ɕϊ�����
	VECTOR screenPos = ConvWorldPosToScreenPos(m_pos);

	if (screenPos.x <= Game::kScreenWidth && screenPos.x >= 0)
	{
		m_isExist = true;
	}
	else
	{
		m_isExist = false;
	}

	// ��ʓ��ɂ��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist) return;

	// �G�z�u
	MV1SetPosition(m_modelHandle, m_pos);

	// TODO:���Ɉړ�������
	//m_pos = VAdd(m_pos, VGet(kMove, 0.0f, 0.0f));
	
	// �����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, m_pos.z, kWidth, kHeight);
}


/// <summary>
/// �`��
/// </summary>
void Enemy::Draw()
{
	if (!m_isExist) return;

	// �R�c���f���̕`��
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG
	// MEMO:�G�̓����蔻��\��
	m_colRect.Draw(0xff00ff, false);
#endif

}


/// <summary>
/// �I��
/// </summary>
void Enemy::End()
{
}
