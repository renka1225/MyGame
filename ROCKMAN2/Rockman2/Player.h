#pragma once
#include "Vec2.h"

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

	int m_handle; // �O���t�B�b�N�̃n���h��
	Vec2 m_pos;	  // �\���ʒu
};

