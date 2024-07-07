#pragma once

class Stage;
class Camera;
class Input;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	// �v���C���[�̏��
	enum class State
	{
		kStand, // �ҋ@
		kRun	// �ړ�
	};

	Player();
	~Player();

	void Init();
	void Update(const Input& input, const Camera& camera, Stage& stage);
	void Draw();

	void OnHitFloor();	// ���ɓ���������

	const VECTOR GetPos() const { return m_pos; }		// �v���C���[�̌��ݒn�擾
	bool GetIsMove() const { return m_isMove; }			// �ړ������ǂ����擾

private:
	// �ړ�����
	void Move(const VECTOR& MoveVector, Stage& stage);
	// �ړ��p�����[�^��ݒ肷��
	State UpdateMoveParameter(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	// �v���C���[�̉�]�𐧌䂷��
	void UpdateAngle();

private:
	// �v���C���[���
	VECTOR m_pos;				// �ʒu
	bool m_isMove;				// �ړ��������ǂ���(true:�ړ�����)
	VECTOR m_targetMoveDir;		// �����ׂ������̃x�N�g��
	float m_angle;				// �����Ă�������̊p�x
	float m_moveSpeed;			// �ړ����x
	State m_currentState;		// ���݂̏��
	int m_modelHandle;			// �v���C���[��3D���f��
};

