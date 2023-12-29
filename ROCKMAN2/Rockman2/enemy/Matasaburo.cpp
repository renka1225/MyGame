#include "Matasaburo.h"
#include "RecoverySmallHp.h"
#include "RecoverySmallShot.h"
#include "SceneMain.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// �ړ����x
	constexpr float kSpeed = 4.0f;

	// �ő�HP
	constexpr int kHp = 3;

	// �����ʒu
	constexpr float kPosX = 900;
	constexpr float kPosY = 500;
}

Matasaburo::Matasaburo() :
	EnemyBase(),
	m_hp(kHp)
{
	m_handle = LoadGraph("data/image/Enemy/matasaburo.png");
}

Matasaburo::~Matasaburo()
{
}

// ������
void Matasaburo::Init()
{
	// HP
	m_hp = kHp;

	// ���݈ʒu
	m_pos.x = kPosX;
	m_pos.y = kPosY;
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

	// ��ʂ��E�ɏo��
	if (m_pos.x > Game::kScreenWidth - width / 2)
	{
		m_isExist = false;
	}
	// ��ʂ�荶�ɏo��
	if (m_pos.x < 0 - width / 2)
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
	m_pos.x = kPosX;
	m_pos.y = kPosY;

	m_vec.x -= 5;
}

void Matasaburo::OnDamage()
{
	// �e������������HP�����炷
	m_hp--;

	// HP��0�ȉ��ɂȂ����瑶�݂�����
	if (m_hp <= 0)
	{
		m_isExist = false;
	}
}