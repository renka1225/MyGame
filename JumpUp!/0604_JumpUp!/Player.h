#pragma once
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
	void Init();
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
	// �p�b�h���͂ɂ���Ĉړ��p�����[�^��ݒ肷��
	State UpdateMoveParameterWithPad(const Input& input, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	void Move(Input& input, Stage& stage);	// �v���C���[�̈ړ�����
	void Jump(Input& input, Stage& state);	// �v���C���[�̃W�����v����
	void UpdateAngle(Stage& stage);			// �v���C���[�̌X���𒲐�����
	float OnHitFloor(Stage& stage);			// �n�ʂ̈ʒu����v���C���[��Y���W�̈ʒu�����߂�
	bool IsHitStage(Stage& stage);			// �X�e�[�W�Ƃ̓����蔻��


private:
	// �v���C���[���
	State m_currentState;		// ���݂̏��
	VECTOR m_pos;				// �v���C���[�ʒu
	VECTOR m_move;				// �ړ���
	float m_angle;				// �����Ă������
	float m_jumpPower;			// Y�������̑��x
	int m_jumpFrame;			// �W�����v�t���[��
	bool m_isJump;				// �W�����v�����ǂ���(true:�W�����v��)
	int m_modelHandle;			// �v���C���[��3D���f��

	// �J�������
	float m_cameraAngle;		// �J�����̊p�x
};

