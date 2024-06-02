#pragma once
#include "DxLib.h"
#include "Collidable.h"
#include <memory>

class Collidable;
class Stage;
class Input;
class DrawDebug;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player : public Collidable
{
public:
	// �v���C���[�̏��
	enum class State
	{
		Idle,	// �ҋ@
		Run,	// �ړ�
		Jump,	// �W�����v��
		Fall,	// ������
	};

	Player();
	virtual ~Player();
	void Init(std::shared_ptr<Physics> physics);
	void Final(std::shared_ptr<Physics> physics);
	void Update(Input& input, Stage& stage);
	void Draw(DrawDebug& drawDebug);
	void OnHit(Stage& stage);	// �Փ˂����Ƃ�

	void OnHitRoof();	// �V��ɓ���������
	void OnHitFloor();	// ���ɓ���������
	void OnFall();		// �������m�肵���Ƃ�

	void SetCameraAngle(float angle) { m_cameraAngle = angle; }

	VECTOR GetPos() const { return m_pos; }				// �v���C���[�̌��ݒn�擾
	State GetState() const { return m_currentState; }	// �v���C���[�̌��݂̏�Ԃ��擾
	VECTOR GetMove() const { return m_move; }			// �v���C���[�̈ړ��ʎ擾

private:
	void Move(Input& input);				// �v���C���[�̈ړ�����
	void Jump(Input& input, Stage& state);	// �v���C���[�̃W�����v����
	void UpdateAngle(Stage& stage);			// �v���C���[�̌X���𒲐�����
	float OnHitFloor(Stage& stage);			// �n�ʂ̈ʒu����v���C���[��Y���W�̈ʒu�����߂�
	bool IsHitStage(Stage& stage);			// �X�e�[�W�Ƃ̓����蔻��

private:

	// �v���C���[���
	VECTOR m_pos;				// �v���C���[�ʒu
	VECTOR m_move;				// �ړ���
	float m_angle;				// �����Ă������
	float m_jumpPower;			// Y�������̑��x
	int m_jumpFrame;			// �W�����v�t���[��
	bool m_isJump;				// �W�����v�����ǂ���(true:�W�����v��)
	int m_modelHandle;			// �v���C���[��3D���f��
	State m_currentState;		// ���݂̏��

	// �J�������
	float m_cameraAngle;

private:	// �萔
	// �v���C���[�̏��
	static constexpr float kScale = 0.1f;		// �v���C���[���f���̊g�嗦
	static constexpr float kMove = 1.0f;		// �v���C���[�ړ���
	static constexpr float kVelocity = 3.0f;	// �W�����v�̍���
	static constexpr float kGravity = -0.2f;	// �d��

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

