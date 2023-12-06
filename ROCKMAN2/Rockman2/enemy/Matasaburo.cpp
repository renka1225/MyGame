#include "Matasaburo.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	constexpr float kSpeed = 4.0f;
}

Matasaburo::Matasaburo() :
	EnemyBase(),
	m_hp(1)
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
	m_pos.x = static_cast<float>(900);
	m_pos.y = static_cast<float>(500);

<<<<<<< HEAD
	m_vec.x -= 5;
}

void Matasaburo::OnDamage()
{
	// �e������������HP�����炷
	m_hp--;

	// HP��0�ȉ��ɂȂ����瑶�݂�����
=======
	// 1�t���[��������̈ړ��x�N�g�������肷��
	m_vec.x = -kSpeed;
}

void Matasaburo::OnDamage(int damage)
{
	// HP�����炷
	m_hp -= damage;

>>>>>>> b7e625657adb768e3ac97a47834cb71cb76e3f7e
	if (m_hp <= 0)
	{
		m_isExist = false;
	}
}
