#pragma once
#include "CharacterBase.h"
#include <memory>

class Stage;
class EnemyBase;
class Camera;
class Input;
class UIGauge;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player : public CharacterBase 
{
public:
	// �v���C���[�̏��
	enum class State
	{
		kAvoid = 0,		// ���
		kDown = 1,		// �|���
		kFightIdle = 2, // �\��
		kGettingUp = 3, // �N���オ��
		kGrab = 4,		// �͂�
		kGuard = 5,		// �K�[�h
		kKick = 6,		// �L�b�N
		kPunch = 7,		// �p���`
		kComboPunch = 8,// �R���{�p���`
		kReceive = 9,	// �U�����󂯂�
		kRun = 10,		// �ړ�
		kStand = 11,	// �ҋ@
		kStumble,		// �͂ݎ��s
	};

	// �A�j���[�V�������
	enum class AnimKind
	{
		kNone = -1,		// �Ȃ�
		kAvoid = 0,		// ���
		kDown = 1,		// �|���
		kFightIdle = 2, // �\��
		kGettingUp = 3, // �N���オ��
		kGrab = 4,		// �͂�
		kGuard = 5,		// �K�[�h
		kKick = 6,		// �L�b�N
		kPunch = 7,		// �p���`
		kComboPunch = 8,// �R���{�p���`
		kReceive = 9,	// �U�����󂯂�
		kRun = 10,		// �ړ�
		kStand = 11,	// �ҋ@
		kStumble,		// �͂ݎ��s
	};

	Player();
	~Player();

	void Init();
	void Update(const Input& input, const Camera& camera, Stage& stage);
	void Draw();

	// �U�����󂯂��ۂ̏���
	void OnDamage();
	// �����蔻����`�F�b�N����
	void CheckHitEnemyCol(EnemyBase& enemy, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius);

	const VECTOR GetPos() const { return m_pos; }	// ���ݒn�擾
	float GetHp() const { return m_hp; }			// ���݂�HP���擾
	bool GetIsMove() const { return m_isMove; }		// �ړ������ǂ����擾

private:
	// �����蔻��̈ʒu�X�V
	void UpdateCol();
	// �ړ�����
	void Move(const VECTOR& MoveVector, Stage& stage);
	// �������
	State Avoidance(const Input& input, VECTOR& moveVec);
	// �ړ��p�����[�^��ݒ肷��
	State UpdateMoveParameter(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	// �U������
	State Attack(const Input& input);
	// �v���C���[�̉�]�𐧌䂷��
	void UpdateAngle();
	// �A�j���[�V�����X�e�[�g�̍X�V
	void UpdateAnimState(State prevState);
	// �A�j���[�V��������
	void UpdateAnim();
	// �A�j���[�V�������Đ�����
	void PlayAnim(AnimKind PlayAnimIndex);

private:
	std::shared_ptr<UIGauge> m_pUIGauge;

	// �v���C���[���
	float m_gauge;				// �Q�[�W��
	VECTOR m_pos;				// �ʒu
	bool m_isMove;				// �ړ��������ǂ���(true:�ړ�����)
	bool m_isAttack;			// �U�������ǂ���(ture:�U����)
	VECTOR m_targetMoveDir;		// �����ׂ������̃x�N�g��
	float m_angle;				// �����Ă�������̊p�x
	float m_moveSpeed;			// �ړ����x
	State m_currentState;		// ���݂̏��
	int m_modelHandle;			// �v���C���[��3D���f��

	// �A�j���[�V�������
	int m_currentPlayAnim;		// �Đ����̃A�j���[�V�����̃A�^�b�`�ԍ�
	float m_currentAnimCount;	// �Đ����̃A�j���[�V�����̍Đ�����
	int m_prevPlayAnim;			// �O�̍Đ��A�j���[�V�����̃A�^�b�`�ԍ�
	float m_prevAnimCount;		// �O�̍Đ��A�j���[�V�����̍Đ�����
	float m_animBlendRate;		// ���݂Ɖߋ��̃A�j���[�V�����̃u�����h��

	// �v���C���[�̓����蔻����
	struct CollisionInfo
	{
		VECTOR hitTopPos;		// �v���C���[�S�̂̓����蔻��̏㕔��
		VECTOR hitBottomPos;	// �v���C���[�S�̂̓����蔻��̉�����
		VECTOR armTopPos;		// �v���C���[�̘r�̐�[�ʒu
		VECTOR armStartPos;		// �v���C���[�̘r�̈ʒu
		VECTOR armEndPos;		// �v���C���[�̘r�̈ʒu
		VECTOR legStartPos;		// �v���C���[�̋r�̈ʒu
		VECTOR legEndPos;		// �v���C���[�̋r�̈ʒu
	};
	CollisionInfo m_col;
};

