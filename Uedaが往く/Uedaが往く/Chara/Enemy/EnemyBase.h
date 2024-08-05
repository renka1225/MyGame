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

	float GetHp() const { return m_hp; }				// �G��HP���擾
	VECTOR GetPos() const { return m_pos; }				// �G�̍��W���擾
	VECTOR GetDir() const { return m_eToPDirVec; }		// �G�̌����x�N�g�����擾

#ifdef _DEBUG
	void DebugDamage(Input& input); // 1�{�^���œG��HP��0�ɂ���
#endif


protected:
	// ��Ԃ��X�V����
	CharacterBase::State UpdateState(Player& player, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	// �ړ�����
	void Move(const VECTOR& moveVec, Player& player, Stage& stage);
	// �p���`����
	CharacterBase::State Punch();
	// �L�b�N����
	CharacterBase::State kick();
	// �������
	CharacterBase::State Avoid();
	// �\������
	CharacterBase::State Fighting();
	// �K�[�h����
	CharacterBase::State Guard();
	// �K�[�h��Ԃ���������
	CharacterBase::State OffGuard();
	// �G�̊p�x���X�V
	void UpdateAngle();

protected:
	int m_stopTime;				// ��~���鎞��
	int m_angleIntervalTime;	// �p�x���X�V����܂ł̎���
	int m_intervalTime;			// ���̏�Ԃ��X�V����܂ł̎���
	VECTOR m_eToPDirVec;		// �G�̈ʒu����v���C���[�ʒu�̃x�N�g��
};

