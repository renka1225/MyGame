#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class Player
{
public:
	Player(SceneMain* pMain);
	~Player();

	void Init();
	void Update();
	void Draw();

	// �����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }
	// �v���C���[�̌��݂̌������擾����
	bool GetDir() const { return m_isRight; }
	// �v���C���[�̌��ݍ��W���擾����
	Vec2 GetPos() const { return m_pos; }
	// �v���C���[�̓����蔻����擾����
	Rect GetColRect() const { return m_colRect; }

	// ���݂̒e�G�l���M�[�����擾����
	float GetMetalEnergy() const { return m_metalEnergy; }
	float GetFireEnergy() const { return m_fireEnergy; }
	float GetLineEnergy() const { return m_lineEnergy; }

	// �{�^���������ė����܂ł̎��Ԃ��擾����
	int GetPressTime() const { return m_nowPressTime; }

private:
	SceneMain* m_pMain;

	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��p�̋�`
	Rect m_colRect;

	// �O���t�B�b�N�̃n���h��
	int m_handle;

	// �����Ă������
	bool m_isRight;
	// �W�����v�����ǂ���
	bool m_isJumpFlag;	// true:�W�����v��
	// �����x
	float m_velocity;

	// HP
	int m_hp;
	// �c�@
	int m_life;

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

