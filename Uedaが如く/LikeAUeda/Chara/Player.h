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
	enum class PlayerState
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

	virtual void Init() override;
	void Update(const Input& input, const Camera& camera, Stage& stage);
	virtual void Draw() override;

	// �U�����󂯂��ۂ̏���
	virtual void OnDamage(float damage) override;
	// �����蔻����`�F�b�N����
	void CheckHitEnemyCol(EnemyBase& enemy, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius);

	const VECTOR GetPos() const { return m_pos; }	// ���ݒn�擾
	float GetHp() const { return m_hp; }			// ���݂�HP���擾
	bool GetIsMove() const { return m_isMove; }		// �ړ������ǂ����擾

private:
	// �����蔻��̈ʒu�X�V
	void UpdateCol();
	// �ړ�����
	void Move(const VECTOR& moveVec, Stage& stage);
	// �������
	PlayerState Avoidance(const Input& input, VECTOR& moveVec);
	// �ړ��p�����[�^��ݒ肷��
	PlayerState UpdateMoveParameter(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	// �U������
	PlayerState Attack(const Input& input);
	// �v���C���[�̉�]�𐧌䂷��
	void UpdateAngle();
	// �A�j���[�V�����X�e�[�g�̍X�V
	void UpdateAnimState(PlayerState prevState);
	// �A�j���[�V��������
	void UpdateAnim();
	// �A�j���[�V�������Đ�����
	void PlayAnim(AnimKind PlayAnimIndex);

private:
	// �v���C���[���
	float m_gauge;				// �Q�[�W��
	bool m_isMove;				// �ړ��������ǂ���(true:�ړ�����)
	bool m_isAttack;			// �U�������ǂ���(ture:�U����)
	VECTOR m_targetMoveDir;		// �����ׂ������̃x�N�g��
	PlayerState m_currentState;	// ���݂̏��

};
