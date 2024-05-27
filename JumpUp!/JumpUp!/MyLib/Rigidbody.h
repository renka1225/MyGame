#pragma once
#include "DxLib.h"

/// <summary>
/// �����E�Փ˔���ɕK�v�ȃf�[�^���Ǘ�����N���X
/// </summary>
class Rigidbody
{
public:
	Rigidbody();
	void Init();

	// ���݂̈ʒu�A���x���Z�b�g
	void SetPos(const VECTOR& set) { m_pos = set; }
	void SetVelocity(const VECTOR& set);

	// ���݂̈ʒu�A�����A���x���擾
	VECTOR GetPos() const { return m_pos; }
	VECTOR GetDir() const { return m_dir; }
	VECTOR GetVelocity() const { return m_velocity; }

private:
	VECTOR m_pos;		// �\���ʒu
	VECTOR m_dir;		// ����
	VECTOR m_velocity;	// ���x
};

