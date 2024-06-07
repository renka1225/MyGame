#pragma once

/// <summary>
/// 3D�̎l�p�̓����蔻�菈�����s��
/// </summary>
class Collision3DBox
{
public:
	Collision3DBox();
	~Collision3DBox() {};

	// �����̂̕`��
	void Draw(unsigned int color, VECTOR pos, VECTOR size);
	// ���S���W�ƕ��������s���w��
	void SetCenter(VECTOR pos, VECTOR size);
	// �o�E���h�{�b�N�X���쐬
	void CreateBoundingBox(int handle);
	// �����̓��m�̓����蔻��
	bool IsCollision(const Collision3DBox& col3DBox);

	// ���S�_�擾
	VECTOR GetCenter() const { return m_centerPos; }	// ��`�̒��S���W

public:
	VECTOR m_minPos;	// ���[�J�����W�ł̍ŏ��l
	VECTOR m_maxPos;	// ���[�J�����W�ł̍ő�l
	VECTOR m_centerPos;	// ���f���̒��S�_

	float m_left;	// ������O��X���W
	float m_bottom;	// ������O��Y���W
	float m_front;	// ������O��Z���W
	float m_right;	// �E�㉜��X���W
	float m_top;	// �E�㉜��Y���W
	float m_back;	// �E�㉜��Z���W
};

