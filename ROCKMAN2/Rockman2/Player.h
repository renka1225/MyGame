#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class Bg;
class RecoveryBase;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player(SceneMain* pMain, Bg* pBg);
	~Player();

	void Init();
	void Update();
	void Draw();

	// �����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }
	// ���݈ʒu���X�V����
	void SetPos(Vec2 pos) { m_pos = pos; }
	// �v���C���[�̌��݂̌������擾����
	bool GetDir() const { return m_isRight; }
	// �v���C���[�̌��ݍ��W���擾����
	Vec2 GetPos() const { return m_pos; }
	// �v���C���[�̓����蔻����擾����
	Rect GetColRect() const { return m_colRect; }

	// ���݂�HP���擾����
	float GetHp() const { return m_hp; }
	// ���݂̎c�@�����擾����
	int GetLife() const { return m_life; }

	// �n�ʂɐڂ��Ă��邩�擾����
	bool GetGround() const { return m_isGround; }

	// ���݂̒e�G�l���M�[�����擾����
	float GetMetalEnergy() const { return m_metalEnergy; }
	float GetFireEnergy() const { return m_fireEnergy; }
	float GetLineEnergy() const { return m_lineEnergy; }

	// �{�^���������ė����܂ł̎��Ԃ��擾����
	int GetPressTime() const { return m_nowPressTime; }

public:
	// �v���C���[���_���[�W���󂯂����̏���
	void OnDamage();
	// �v���C���[�̉񕜏���
	void HpSmallRecovery();		// HP����
	void HpGreatRecovery();		// HP���
	void HpFullRecovery();		// HP�S��
	void ShotSmallRecovery();	// �e����
	void ShotGreatRecovery();	// �e���
	void LifeRecovery();		// �c�@��

private:
	SceneMain* m_pMain;
	Bg* m_pBg;
	RecoveryBase* m_pRecovery;

	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��p�̋�`
	Rect m_colRect;

	// �O���t�B�b�N�̃n���h��
	int m_handle;

	// �����Ă������
	bool m_isRight;
	// �n�ʂƐڂ��Ă��邩
	bool m_isGround;	// true:�ڂ��Ă���
	// �����x
	float m_velocity;
	// �W�����v���̃t���[����
	int m_jumpFrame;

	// HP
	int m_hp;
	// �c�@
	int m_life;

	// �_���[�W���󂯂Ă���̃t���[����
	int m_damageFrame;

	// ���^���̒e�G�l���M�[��
	float m_metalEnergy;
	// �t�@�C���[�̒e�G�l���M�[��
	float m_fireEnergy;
	// �A�C�e��2���̒e�G�l���M�[��
	float m_lineEnergy;

	// �{�^���̏�Ԃ��擾����
	int m_keyState;
	// �{�^�������������ꂽ����
	int m_pressTime;
	// �{�^���������ė����܂ł̎���
	int m_nowPressTime;
};

