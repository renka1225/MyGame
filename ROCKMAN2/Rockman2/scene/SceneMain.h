#pragma once
#include <vector>
#include "Vec2.h"

class Player;
class Bg;
class ShotBase;
class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void End();
	void Update();
	void Draw();

	// �V���b�g�̒ǉ�
	// �o�^�ł��Ȃ������ꍇ��false��Ԃ��A������pShot���������
	bool AddShot(ShotBase* pShot);


private:
	// �O���t�B�b�N�̃n���h��
	int m_bgHandle;			// �w�i
	int m_playerHandle;		// �v���C���[

	// �w�i
	Bg* m_pBg;
	// �v���C���[
	Player* m_pPlayer;
	// �V���b�g
	std::vector<ShotBase*> m_pShot;

};

