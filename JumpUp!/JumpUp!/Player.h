#pragma once
#include "DxLib.h"
#include <memory>

class Stage;
class Input;
class DrawDebug;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player();
	~Player();
	void Init();
	void Update(Input& input, std::shared_ptr<Stage> stage);
	void Draw(DrawDebug& drawDebug);

	void SetCameraAngle(float angle) { m_cameraAngle = angle; }

private:
	void Move(Input& input);	// �v���C���[�̈ړ�����
	void Jump(Input& input);	// �v���C���[�̃W�����v����
	void HitPlane();			// �n�ʂɓ��������ۂ̏���
	void UpdateRotate();		// �v���C���[�̌X���𒲐�����

private:
	std::shared_ptr<Stage> m_stage;

	// �v���C���[���
	VECTOR m_pos;		// �v���C���[�ʒu
	VECTOR m_move;		// �ړ���
	float m_angle;		// �����Ă������
	int m_jumpFrame;	// �W�����v�t���[��
	bool m_isJump;		// �W�����v�t���O true:�W�����v��
	int m_modelHandle;	// �v���C���[��3D���f��

	// �J�������
	float m_cameraAngle;

private:	// �萔
	// �v���C���[�̏��
	static constexpr float kScale = 0.1f;		// �v���C���[���f���̊g�嗦
	static constexpr float kMove = 1.0f;		// �v���C���[�ړ���
	static constexpr float kVelocity = 15.0f;	// �W�����v�̍���
	static constexpr float kGravity = -1.8f;	// �d��

	// �����蔻��
	static constexpr float kCenterPosY = 12.0f;	// �v���C���[�̒��S�_�𒲐�
	static constexpr float kWidth = 10.0f;		// ����
	static constexpr float kHeight = 24.0f;		// �c��
	static constexpr float kDepth = 5.0f;		// ���s���̕�

	// �W�����v�t���[��
	static constexpr int kLittleJumpFrame = 10;			// ���W�����v
	static constexpr int kMediumJumpFrame = 30;			// ���W�����v
	// �W�����v�̍���
	static constexpr float kLittleJumpHeight = 0.5f;	// ���W�����v
	static constexpr float kMediumJumpHeight = 0.8f;	// ���W�����v
	static constexpr float kBigJumpHeight = 1.0f;		// ��W�����v
};

