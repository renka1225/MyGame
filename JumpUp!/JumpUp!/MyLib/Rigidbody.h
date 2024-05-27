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
	// ���f���̃T�C�Y���Z�b�g
	void SetScale(const VECTOR& set) { m_pos = set; }

	// ���݂̈ʒu�A�����A���x���擾
	VECTOR GetPos() const { return m_pos; }
	VECTOR GetDir() const { return m_dir; }
	VECTOR GetVelocity() const { return m_velocity; }
	// ���f���̃T�C�Y���擾
	VECTOR GetScale() const { return m_scale; }

private:
	VECTOR m_pos;		// �\���ʒu
	VECTOR m_dir;		// ����
	VECTOR m_velocity;	// ���x
	VECTOR m_scale;		// �T�C�Y
};

