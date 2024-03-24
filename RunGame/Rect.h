#pragma once
#include "DxLib.h"

/// <summary>
/// ��`�̍��W���Ǘ�����N���X
/// </summary>
class Rect
{
public:
	Rect();
	virtual ~Rect();
	// �l�p�̕`��
	void Draw(unsigned int color, bool isFill);
	// ���S���W�ƕ��������w��
	void SetCenter(float x, float y, float width, float height);

	// ���擾
	float GetWidth() const;			// ��`�̕�
	float GetHeight() const;		// ��`�̍���
	VECTOR GetCenter() const;		// ��`�̒��S���W

	// ��`���m�̓����蔻��
	bool IsCollision(const Rect& rect);

private:
	float m_left;	// �����X���W
	float m_top;	// �����Y���W
	float m_right;	// �E����X���W
	float m_bottom;	// �E����Y���W
};

