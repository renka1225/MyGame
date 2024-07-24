#pragma once
#include "CharacterBase.h"
#include <memory>

class Player;
class Stage;

/// <summary>
/// �G�̊��N���X
/// </summary>
class EnemyBase : public CharacterBase
{
public:
	// �G�l�~�[�̏��
	enum class EnemyState
	{
		kAvoid = 0,		// ���
		kDown = 1,		// �|���
		kFightIdle = 2, // �\��(��~��)
		kFightWalk = 3, // �\��(�ړ���)
		kGettingUp = 4, // �N���オ��
		kGrab = 5,		// �͂�
		kGuard = 6,		// �K�[�h
		kKick = 7,		// �L�b�N
		kPunch = 8,		// �p���`
		kComboPunch = 9,// �R���{�p���`
		kReceive = 10,	// �U�����󂯂�
		kRun = 11,		// �ړ�
		kStand = 12,	// �ҋ@
		kStumble = 13,	// �͂ݎ��s
	};

	EnemyBase();
	virtual ~EnemyBase();
	virtual void Init() = 0;
	virtual void Update(Player& player, Stage& stage) = 0;
	virtual void Draw() = 0;

	// �v���C���[�Ƃ̓����蔻����`�F�b�N����
	void CheckHitPlayerCol(Player& player, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius);

	float GetHp() const { return m_hp; }	// �G��HP���擾
	VECTOR GetPos() const { return m_pos; } // �G�̍��W���擾

protected:
	// �G�̎��̍s�������߂�
	void DecideNextAction();
	// �ړ�����
	void Move(const VECTOR& moveVec, Player& player, Stage& stage);
	// �ړ��p�����[�^��ݒ肷��
	EnemyState UpdateMoveParameter(Player& player, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	// �U������
	EnemyState Attack();
	// �G�̊p�x���X�V
	void UpdateAngle(Player& player);
	// �A�j���[�V�����X�e�[�g�̍X�V
	void UpdateAnimState(EnemyState prevState);
	// �A�j���[�V��������
	virtual void UpdateAnim() override;

protected:
	bool m_isMove;				// �ړ��������ǂ���(true:�ړ�����)
	bool m_isAttack;			// �U�������ǂ���(ture:�U����)
	int m_stopFrame;			// ��~����t���[����
	int m_angleFrame;			// �p�x���X�V����t���[����
	EnemyState m_currentState;	// �G�l�~�[�̌��݂̏��
};

