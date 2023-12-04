#include "EnemyBase.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>

EnemyBase::EnemyBase():
	m_handle(-1),
	m_isExist(false)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
}

void EnemyBase::Update()
{
	// ���݂��Ȃ��G�̏����͂��Ȃ�
	if (!m_isExist) return;

	// �O���t�B�b�N���ݒ肳��Ă��Ȃ���Ύ~�܂�
	assert(m_handle != -1);
}

void EnemyBase::Draw()
{
	// ���S�ʒu����Ƃ��ĕ`�悷��
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), 1.0, 0.0, m_handle, true, false);

#ifdef _DEBUG
	// �����蔻��̕\��
	m_colRect.Draw(0x00ff00, false);
#endif
}

void EnemyBase::Start()
{
	m_isExist = false;
}

void EnemyBase::UpdateCollision()
{
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	// ���S���W���w�肵�ē����蔻���Rect�𐶐�����
	m_colRect.SetCenter(m_pos.x, m_pos.y, width, height);
}
