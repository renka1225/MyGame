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
	~Player();
	void Init();
	void Update(Input& input);
	void Draw();

private:
	void Move(Input& input);	// �v���C���[�̈ړ�����
	void Jump(Input& input);	// �v���C���[�̃W�����v����

private:
	VECTOR m_pos;		// �v���C���[�ʒu
	VECTOR m_move;		// �ړ���
	int m_jumpFrame;	// �W�����v�t���[��
	bool m_isJump;		// �W�����v�t���O true:�W�����v��
	int m_modelHandle;	// �v���C���[��3D���f��

private:
	static constexpr float kScale = 0.1f;		// �v���C���[���f���̊g�嗦
	static constexpr float kMove = 1.0f;		// �v���C���[�ړ���
	static constexpr float kVelocity = 15.0f;	// �W�����v�̍���
	static constexpr float kGravity = -1.8f;	// �d��

	// �W�����v�t���[��
	static constexpr int kLittleJumpFrame = 10;			// ���W�����v
	static constexpr int kMediumJumpFrame = 30;			// ���W�����v
	// �W�����v�̍���
	static constexpr float kLittleJumpHeight = 0.5f;	// ���W�����v
	static constexpr float kMediumJumpHeight = 0.8f;	// ���W�����v
	static constexpr float kBigJumpHeight = 1.0f;		// ��W�����v
};

