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
	// �v���C���[�̌��ݍ��W���擾����
	Vec2 GetPos() const { return m_pos; }

private:
	SceneMain* m_pMain;

	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��p�̋�`
	Rect m_colRect;
	// �O���t�B�b�N�̃n���h��
	int m_handle;
	// �W�����v�̃t���[����
	int m_jumpFrame;
	// �W�����v�����ǂ���
	bool m_isJumpFlag;
	// HP
	int m_hp;
	// �c�@
	int m_life;
};

