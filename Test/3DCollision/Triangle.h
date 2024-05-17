#pragma once
#include "DxLib.h"

/// <summary>
/// �O�p�`�N���X
/// </summary>
class Triangle
{
public:
	Triangle();
	~Triangle() {};
	void Draw();

	// ���_1���擾
	VECTOR GetPos1() const { return m_pos1; }
	// ���_2���擾
	VECTOR GetPos2() const { return m_pos2; }
	// ���_3���擾
	VECTOR GetPos3() const { return m_pos3; }

private:
	// ���_1�̍��W
	VECTOR m_pos1;
	// ���_2�̍��W
	VECTOR m_pos2;
	// ���_3�̍��W
	VECTOR m_pos3;
};