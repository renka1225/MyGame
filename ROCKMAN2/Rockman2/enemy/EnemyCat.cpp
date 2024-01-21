#include "EnemyCat.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// �G�̃T�C�Y
	constexpr int kWidth = 30;
	constexpr int kHeight = 64;
	// �g�嗦
	constexpr float kEnlarge = 3.0f;

	// �ړ����x
	constexpr float kSpeed = 2.0f;

	// �ő�HP
	constexpr int kHp = 5;
}


EnemyCat::EnemyCat()
{
	m_handle = LoadGraph("data/image/Enemy/cat.png");
}

EnemyCat::~EnemyCat()
{
	DeleteGraph(m_handle);
}

void EnemyCat::Init()
{
	m_hp = kHp;
}

void EnemyCat::Update()
{
	// ���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist) return;

	// ���݈ʒu�̍X�V
	m_pos += m_vec;

	// TODO:�G�����E�Ɉړ�������
	if (m_pos.x < 500 || m_pos.x > 1000)
	{
		m_vec.x *= -1;
	}

	// ��ʊO�ɏo������
	bool isOut = false;	// �`�F�b�N���̍��W����ʊO���ǂ����t���O
	if (m_pos.x < 0.0f - kWidth / 2) isOut = true; // ��ʍ��[
	if (m_pos.x > Game::kScreenWidth + kWidth / 2) isOut = true; // ��ʉE�[

	// ��ʓ��Ȃ炱���ŏI��
	if (!isOut) return;

	// ��ʊO�ɏo����I������
	m_isExist = false;

	// �����蔻��𐶐�
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kWidth), static_cast<float>(kHeight));
}

void EnemyCat::Draw()
{
	DrawRectRotaGraph(static_cast<int>(m_pos.x + kWidth * 0.5f), static_cast<int>(m_pos.y + kHeight * 0.5f), 0, 0, kWidth, kHeight, kEnlarge, 0.0f, m_handle, true, false);

#ifdef _DEBUG
	// �����蔻��̕\��
	m_colRect.Draw(0x00ff00, false);
#endif
}

void EnemyCat::Start()
{
	// �G�L�����N�^�[��o�ꂳ����
	m_isExist = true;

	m_pos = { 1000, 700 };
	m_vec.x -= kSpeed;
}

void EnemyCat::OnDamage()
{
	// �e������������HP�����炷
	m_hp--;

	// HP��0�ȉ��ɂȂ����瑶�݂�����
	if (m_hp <= 0)
	{
		m_isExist = false;
	}
}
