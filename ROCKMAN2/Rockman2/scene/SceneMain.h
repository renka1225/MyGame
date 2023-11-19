#pragma once
#include <vector>
#include "Vec2.h"

class Player;
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


private:
	// �O���t�B�b�N�̃n���h��
	int m_playerHandle; // �v���C���[

	// �v���C���[
	Player* m_pPlayer;
};

