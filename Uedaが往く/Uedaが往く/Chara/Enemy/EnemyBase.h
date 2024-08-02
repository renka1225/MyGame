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
	EnemyBase();
	virtual ~EnemyBase();
	virtual void Init() = 0;
	virtual void Update(Player& player, Stage& stage) = 0;
	virtual void Draw() = 0;

	// �v���C���[�Ƃ̓����蔻����`�F�b�N����
	void CheckHitPlayerCol(Player& player, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius);

	float GetHp() const { return m_hp; }	// �G��HP���擾
	VECTOR GetPos() const { return m_pos; } // �G�̍��W���擾

#ifdef _DEBUG
	void DebugDamage(Input& input); // 1�{�^���œG��HP��0�ɂ���
#endif


protected:
	// �ړ�����
	void Move(const VECTOR& moveVec, Player& player, Stage& stage);
	// �ړ��p�����[�^��ݒ肷��
	CharacterBase::State UpdateMoveParameter(Player& player, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	// �p���`����
	void Punch();
	// �L�b�N����
	void kick();
	// �������
	void Avoidance(VECTOR& moveVec);
	// �\������
	void Fighting();
	// �K�[�h����
	void Guard();
	// �K�[�h��Ԃ���������
	void OffGuard();
	// �G�̊p�x���X�V
	void UpdateAngle(Player& player);

protected:
	bool m_isMove;				// �ړ��������ǂ���(true:�ړ�����)
	bool m_isAttack;			// �U�������ǂ���(ture:�U����)
	int m_stopTime;				// ��~���鎞��
	int m_angleIntervalTime;	// �p�x���X�V����܂ł̎���
	int m_intervalTime;			// ���̏�Ԃ��X�V����܂ł̎���
};

