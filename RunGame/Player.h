#pragma once
#include "DxLib.h"

class Input;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player();
	virtual ~Player();
	void Init();
	void Update(Input& input);
	void Draw();
	void End();

	VECTOR GetPos() const { return m_pos; }

private:
	// �W�����v����
	void Jump(Input& input);

private:
	// �\���ʒu
	VECTOR m_pos;
	// �ړ���
	VECTOR m_move;

	// �W�����v�t���O true:�W�����v��
	bool m_isJump;
	// �W�����v�t���[��
	int m_jumpFrame;

	// 3D���f��
	int m_handle;
};