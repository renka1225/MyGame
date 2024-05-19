#pragma once
#include "DxLib.h"

/// <summary>
/// ������2�N���X
/// </summary>
class Cube2
{
public:
	Cube2();
	~Cube2() {};
	void Draw();

	// �����̂̒��S�_���擾
	VECTOR GetPos() const { return m_pos; }
	// �����̂̃T�C�Y���擾
	VECTOR GetScale() const { return m_scale; }

private:
	// ������2�̒��S�_
	VECTOR m_pos;
	// ������2�̃T�C�Y
	VECTOR m_scale;

	// �����̂�3D���f��
	int m_handle;
};

