#include "Rect.h"
#include "Game.h"
#include <cassert>

Rect::Rect():
	m_left(0.0f),
	m_top(0.0f),
	m_right(0.0f),
	m_bottom(0.0f)
{
}

Rect::~Rect()
{
}

void Rect::Draw(unsigned int color, bool isFill)
{
	DrawBox(static_cast<int>(m_left), static_cast<int>(m_top),
		static_cast<int>(m_right), static_cast<int>(m_bottom),
		color, isFill);
}

void Rect::SetCenter(float x, float y, float z, float width, float height)
{
	// ���[���h���W����X�N���[�����W�ɕϊ�
	VECTOR screenPos = ConvWorldPosToScreenPos(VGet(x, y, z));

	m_left = screenPos.x - width * 0.5f;
	m_top = screenPos.y - height * 0.5f;
	m_right = screenPos.x +  width * 0.5f;
	m_bottom = screenPos.y + height * 0.5f;
}

float Rect::GetWidth() const
{
	assert(m_right >= m_left);	// ���E�̍��W����ւ��`�F�b�N
	return m_right - m_left;
}

float Rect::GetHeight() const
{
	assert(m_top >= m_bottom);	// �㉺�̍��W����ւ��`�F�b�N
	return  m_top - m_bottom;
}

VECTOR Rect::GetCenter() const
{
	// ���S���W
	float x = (m_left + m_right) * 0.5f;
	float y = (m_top + m_bottom) * 0.5f;
	float z = 0.0f;
	return VECTOR{x, y, z};
}

bool Rect::IsCollision(const Rect& rect)
{
	// ��΂ɓ�����Ȃ��p�^�[�����͂����Ă���
	if (m_left > rect.m_right) return false;
	if (m_top > rect.m_bottom) return false;
	if (m_right < rect.m_left) return false;
	if (m_bottom < rect.m_top) return false;

	// ������Ȃ��p�^�[���ȊO�͓������Ă���
	return true;
}
