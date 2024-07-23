#pragma once
#include <memory>

class LoadData;
class UIGauge;

/// <summary>
/// �L�����N�^�[�̊��N���X
/// </summary>
class CharacterBase
{
public:
	CharacterBase();
	~CharacterBase() {};
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void OnDamage(float damage);		// �_���[�W���󂯂��ۂ̏���

	VECTOR GetPos() const { return m_pos; }			// ���ݒn�擾
	float GetHp() const { return m_hp; }			// ���݂�HP���擾
	bool GetIsGuard() const { return m_isGuard; }	// �K�[�h�����ǂ����擾

	// �L�����N�^�[�̎��
	enum class CharaType
	{
		kPlayer,	// �v���C���[
		kEnemyTuto,	// �`���[�g���A���̓G
	};

	// �A�j���[�V�������
	enum class AnimKind
	{
		kNone = -1,		// �Ȃ�
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

	// �A�j���[�V�������x
	struct AnimSpeed
	{
		float none;			// �Ȃ�
		float avoid;		// ���
		float down;			// �|���
		float fightIdle;	// �\��(��~��)
		float fightWalk;	// �\��(�ړ���)
		float gettingUp;	// �N���オ��
		float grab;			// �͂�
		float guard;		// �K�[�h
		float kick;			// �L�b�N
		float punch;		// �p���`
		float comboPunch;	// �R���{�p���`
		float receive;		// �U�����󂯂�
		float run;			// �ړ�
		float stand;		// �ҋ@
		float Stumble;		// �͂ݎ��s
	};
	AnimSpeed m_animSpeed;

	// �L�����N�^�[�̃X�e�[�^�X
	struct Status
	{
		float maxHp;			// �ő�HP
		float punchPower;		// �p���`�̍U����
		float kickPower;		// �L�b�N�̍U����
		float maxMoveSpeed;		// �ő�̈ړ����x
		float fightWalkSpeed;	// �\�����̈ړ����x
		float acceleration;		// �����x
		float deceleration;		// �����x
		float avoidDist;		// ����̋���
	};
	Status m_status;

	// �����蔻����
	struct CollisionInfo
	{
		float bodyHeight;		// �S�g�̓����蔻��̍���
		float bodyRadius;		// �S�g�̓����蔻��̔��a
		float aimRadius;		// �r�̓����蔻��̔��a
		float legRadius;		// �r�̓����蔻��̔��a
		VECTOR armStartPos;		// �r�̓����蔻��n�_
		VECTOR armEndPos;		// �r�̓����蔻��I�_
		VECTOR legStartPos;		// �r�̓����蔻��n�_
		VECTOR legEndPos;		// �r�̓����蔻��I�_
		VECTOR bodyTopPos;		// �S�g�̓����蔻��n�_
		VECTOR bodyBottomPos;	// �S�g�̓����蔻��I�_
	};
	CollisionInfo m_colInfo;

protected:
	// �����蔻��ʒu�̍X�V
	void UpdateCol();
	// �A�j���[�V�������Đ�����
	void PlayAnim(AnimKind playAnimIndex);
	// �A�j���[�V��������
	virtual void UpdateAnim() = 0;
	
protected:
	std::shared_ptr<LoadData> m_pLoadData;	// �L�����N�^�[�����擾
	std::shared_ptr<UIGauge> m_pUIGauge;	// �o�g�����ɕ\������HP�̃Q�[�W

	float m_hp;			// HP
	VECTOR m_pos;		// �ʒu
	float m_moveSpeed;	// �ړ����x
	float m_angle;		// �����Ă�������̊p�x
	bool m_isAttack;	// �U�������ǂ���(true:�U����)
	bool m_isGuard;		// �K�[�h�����ǂ���(ture:�K�[�h��)
	int m_modelHandle;	// �L�����N�^�[��3D���f��

	// �A�j���[�V�������
	int m_currentPlayAnim;		// �Đ����̃A�j���[�V�����̃A�^�b�`�ԍ�
	float m_currentAnimCount;	// �Đ����̃A�j���[�V�����̍Đ�����
	int m_prevPlayAnim;			// �O�̍Đ��A�j���[�V�����̃A�^�b�`�ԍ�
	float m_prevAnimCount;		// �O�̍Đ��A�j���[�V�����̍Đ�����
	float m_animBlendRate;		// ���݂Ɖߋ��̃A�j���[�V�����̃u�����h��

	struct Collision
	{
		VECTOR armStartPos;		// �r�̓����蔻��n�_
		VECTOR armEndPos;		// �r�̓����蔻��I�_
		VECTOR legStartPos;		// �r�̓����蔻��n�_
		VECTOR legEndPos;		// �r�̓����蔻��I�_
		VECTOR bodyTopPos;		// �S�g�̓����蔻��n�_
		VECTOR bodyBottomPos;	// �S�g�̓����蔻��I�_
	};
	Collision m_col;
};