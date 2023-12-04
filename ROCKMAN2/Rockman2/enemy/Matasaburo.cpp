#include "Matasaburo.h"
#include "ShotBase.h"
#include "Game.h"
#include "DxLib.h"

Matasaburo::Matasaburo() :
	EnemyBase(),
	m_hp(3)
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

	// �e�Ƃ̓����蔻��
	for (int i = 0; i < m_pShot.size(); i++)
	{
		if (m_pShot[i])
		{
			Rect shotRect = m_pShot[i]->GetColRect();
			if (shotRect.IsCollision(m_colRect))
			{
				// �e������������HP�����炷
				m_hp--;

				// HP��0�ȉ��ɂȂ�����G���폜
				if (m_hp <= 0)
				{
					m_isExist = false;
				}
			}
		}
	}
}

void Matasaburo::Draw()
{
	// ���S�ʒu����Ƃ��ĕ`�悷��
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), 1.0, 0.0, m_handle, true, false);

#ifdef _DEBUG
	// �����蔻��̕\��
	m_colRect.Draw(0x00ff00, false);
#endif
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
