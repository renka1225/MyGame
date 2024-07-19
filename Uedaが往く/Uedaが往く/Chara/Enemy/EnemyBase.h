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

	EnemyBase();
	virtual ~EnemyBase();
	virtual void Init() = 0;
	virtual void Update(Player& player, Stage& stage) = 0;
	virtual void Draw() = 0;

	float GetHp() const { return m_hp; }	// �G��HP���擾
	VECTOR GetPos() const { return m_pos; } // �G�̍��W���擾

protected:
	// �ړ�����
	void Move(const VECTOR& moveVec, Player& player, Stage& stage);
	// �ړ��p�����[�^��ݒ肷��
	EnemyState UpdateMoveParameter(Player& player, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	// �U������
	EnemyState Attack();
	// �G�̊p�x���X�V
	void UpdateAngle(Player& player);
	// �v���C���[�Ƃ̓����蔻����`�F�b�N����
	void CheckHitPlayerColl(Player& player, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius);
	// �A�j���[�V�����X�e�[�g�̍X�V
	void UpdateAnimState(EnemyState prevState);
	// �A�j���[�V��������
	virtual void UpdateAnim() override;

protected:
	bool m_isMove;				// �ړ��������ǂ���(true:�ړ�����)
	bool m_isAttack;			// �U�������ǂ���(ture:�U����)
	int m_stopFrame;			// ��~���鎞��
	EnemyState m_currentState;	// �G�l�~�[�̌��݂̏��
};

