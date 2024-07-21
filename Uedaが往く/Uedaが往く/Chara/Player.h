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

	Player();
	~Player();

	virtual void Init() override;
	void Update(const Input& input, const Camera& camera, EnemyBase& enemy, Stage& stage);
	virtual void Draw() override;

	// �G�l�~�[�Ƃ̓����蔻����`�F�b�N����
	void CheckHitEnemyCol(EnemyBase& enemy, VECTOR eCapPosTop, VECTOR eCapPosBottom, float eCapRadius);

	bool GetIsMove() const { return m_isMove; }		// �ړ������ǂ����擾

private:
	// �ړ�����
	void Move(const VECTOR& moveVec, Stage& stage);
	// �p���`����
	PlayerState Punch(const Input& input);
	// �L�b�N����
	PlayerState Kick(const Input& input);
	// �������
	PlayerState Avoidance(const Input& input, VECTOR& moveVec);
	// �ړ��p�����[�^��ݒ肷��
	PlayerState UpdateMoveParameter(const Input& input, const Camera& camera, VECTOR& upMoveVec, VECTOR& leftMoveVec, VECTOR& moveVec);
	// �v���C���[�̉�]�𐧌䂷��
	void UpdateAngle();
	// �A�j���[�V�����X�e�[�g�̍X�V
	void UpdateAnimState(PlayerState prevState);
	// �A�j���[�V��������
	virtual void UpdateAnim() override;

private:
	// �v���C���[���
	float m_gauge;				// �Q�[�W��
	int m_punchCount;			// ���݂̃p���`�̃R���{��
	int m_punchComboTime;		// �R���{���͎�t����
	int m_punchCoolTime;		// �p���`�ł��Ȃ�����
	int m_avoidCount;			// ���������
	int m_avoidCoolTime;		// ����ł��Ȃ�����
	bool m_isMove;				// �ړ��������ǂ���(true:�ړ�����)
	VECTOR m_targetMoveDir;		// �����ׂ������̃x�N�g��
	PlayerState m_currentState;	// ���݂̏��
};
