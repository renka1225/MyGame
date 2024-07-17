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
	// �L�����N�^�[�̎��
	enum class CharaType
	{
		kPlayer,	// �v���C���[
		kEnemyTuto,	// �`���[�g���A���̓G
	};

	// �L�����N�^�[�̃X�e�[�^�X
	struct Status
	{
		float maxHp;			// �ő�HP
		float punchPower;		// �p���`�̍U����
		float kickPower;		// �L�b�N�̍U����
		float maxMoveSpeed;		// �ő�̈ړ����x
	};
	Status m_status;

	CharacterBase();
	~CharacterBase() {};
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void OnDamage(float damage);	// �_���[�W���󂯂��ۂ̏���

	VECTOR GetPos() const { return m_pos; }	// ���ݒn�擾
	float GetHp() const { return m_hp; }	// ���݂�HP���擾

protected:
	//// �A�j���[�V�����X�e�[�g�̍X�V
	//void UpdateAnimState(State prevState);
	//// �A�j���[�V��������
	//void UpdateAnim();
	//// �A�j���[�V�������Đ�����
	//void PlayAnim(AnimKind PlayAnimIndex);

protected:
	std::shared_ptr<LoadData> m_pLoadData;	// �L�����N�^�[�����擾
	std::shared_ptr<UIGauge> m_pUIGauge;	// �o�g�����ɕ\������HP�̃Q�[�W

	float m_hp;			// HP
	VECTOR m_pos;		// �ʒu
	float m_moveSpeed;	// �ړ����x
	float m_angle;		// �����Ă�������̊p�x
	int m_modelHandle;	// �L�����N�^�[��3D���f��

	// �A�j���[�V�������
	int m_currentPlayAnim;		// �Đ����̃A�j���[�V�����̃A�^�b�`�ԍ�
	float m_currentAnimCount;	// �Đ����̃A�j���[�V�����̍Đ�����
	int m_prevPlayAnim;			// �O�̍Đ��A�j���[�V�����̃A�^�b�`�ԍ�
	float m_prevAnimCount;		// �O�̍Đ��A�j���[�V�����̍Đ�����
	float m_animBlendRate;		// ���݂Ɖߋ��̃A�j���[�V�����̃u�����h��

	// �����蔻����
	struct CollisionInfo
	{
		// �S�g�̓����蔻��
		VECTOR hitTopPos;
		VECTOR hitBottomPos;
		// �r�����̓����蔻��
		VECTOR armStartPos;
		VECTOR armEndPos;
		// �r�����̓����蔻��
		VECTOR legStartPos;
		VECTOR legEndPos;
	};
	CollisionInfo m_col;
};