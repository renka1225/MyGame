#pragma once
#include "DxLib.h"
#include "MyLib.h"
#include <memory>

class Collidable;
class Physics;
class Stage;
class Input;
class DrawDebug;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player : public Collidable
{
public:
	Player(std::shared_ptr<Physics> physics);
	virtual ~Player();
	void Init();
	void End();
	void Update(Input& input, Stage& stage);
	void Draw(DrawDebug& drawDebug);
	void OnCollide();	// �Փ˂����Ƃ�

	void SetCameraAngle(float angle) { m_cameraAngle = angle; }

	VECTOR GetPos() const { return m_pos; }

private:
	void Move(Input& input);			// �v���C���[�̈ړ�����
	void Jump(Input& input);			// �v���C���[�̃W�����v����
	void UpdateAngle(Stage& stage);		// �v���C���[�̌X���𒲐�����
	float GroundHeight(Stage& stage);	// �n�ʂ̍������v�Z����

private:
	std::shared_ptr<Physics> m_pPhysics;

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
	static constexpr float kGravity = -1.5f;	// �d��

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

