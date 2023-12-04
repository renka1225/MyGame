#include "Matasaburo.h"
#include "Game.h"
#include "DxLib.h"

Matasaburo::Matasaburo():
	EnemyBase()
{
	m_handle = LoadGraph("data/image/Enemy/matasaburo.png");
}

Matasaburo::~Matasaburo()
{
}

void Matasaburo::Update()
{
	// ���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist) return;

	// ���݈ʒu�̍X�V
	m_pos += m_vec;

	// �����蔻��̍X�V
	UpdateCollision();

	// ��ʊO�ɏo���瑶�݂�����
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	if (m_pos.x > Game::kScreenWidth - width / 2)
	{
		m_isExist = false;
	}
}

void Matasaburo::Start()
{
	// �G�L�����N�^�[��o�ꂳ����
	m_isExist = true;

	// �摜�T�C�Y
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	// ���݈ʒu
	m_pos.x = static_cast<float>(800);
	m_pos.y = static_cast<float>(500);
}
