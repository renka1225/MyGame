#pragma once

class Stage;
class Camera;
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
		kStand, // �ҋ@
		kFall,	// ������
		kJump,	// �W�����v��
		kRun	// �ړ�
	};

	// �A�j���[�V�������
	enum class AnimKind
	{
		kNone = -1,		// �Ȃ�
		kUnKnown = 0,	// �s��
		kStand = 36,	// �ҋ@
		kFall = 40,		// ����
		kJump = 42,		// �W�����v
		kRun = 48,		// �ړ�
	};

	Player();
	~Player();

	void Init();
	void Update(const Input& input, const Camera& camera, Stage& stage);
	void Draw(DrawDebug& drawDebug);

	void OnHitRoof();	// �V��ɓ���������
	void OnHitFloor();	// ���ɓ���������
	void OnFall();		// �������m�肵���Ƃ�

	const VECTOR GetPos() const { return m_pos; }		// �v���C���[�̌��ݒn�擾
	bool GetIsMove() const { return m_isMove; }			// �ړ������ǂ����擾
	State GetState() const { return m_currentState; }	// �v���C���[�̌��݂̏�Ԃ��擾
	float GetJumpPower() const { return m_jumpPower; }	// �v���C���[�̃W�����v�ʎ擾
	bool GetIsGoal() const { return m_isGoal; }			// �v���C���[���S�[���������擾����

private:
	// �ړ�����
	void Move(const VECTOR& MoveVector, Stage& stage);
	// �ړ��p�����[�^��ݒ肷��
	State UpdateMoveParameter(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	// �v���C���[�̉�]�𐧌䂷��
	void UpdateAngle();
	// �A�j���[�V�����X�e�[�g�̍X�V
	void UpdateAnimState(State prevState);
	// �A�j���[�V��������
	void UpdateAnim();
	// �A�j���[�V�������Đ�����
	void PlayAnim(AnimKind PlayAnimIndex);

private:
	// �v���C���[���
	VECTOR m_pos;				// �ʒu
	bool m_isMove;				// �ړ��������ǂ���(true:�ړ�����)
	VECTOR m_targetMoveDir;		// �����ׂ������̃x�N�g��
	float m_angle;				// �����Ă�������̊p�x
	float m_jumpPower;			// Y�������̑��x
	float m_moveSpeed;			// �ړ����x
	bool m_isGoal;				// �v���C���[���S�[��������
	int m_modelHandle;			// �v���C���[��3D���f��
	State m_currentState;		// ���݂̏��

	// �A�j���[�V�������
	int m_currentPlayAnim;		// �Đ����̃A�j���[�V�����̃A�^�b�`�ԍ�
	float m_currentAnimCount;	// �Đ����̃A�j���[�V�����̍Đ�����
	int m_prevPlayAnim;			// �O�̍Đ��A�j���[�V�����̃A�^�b�`�ԍ�
	float m_prevAnimCount;		// �O�̍Đ��A�j���[�V�����̍Đ�����
	float m_animBlendRate;		// ���݂Ɖߋ��̃A�j���[�V�����̃u�����h��
};

