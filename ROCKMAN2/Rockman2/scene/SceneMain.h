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
	// グラフィックのハンドル
	int m_playerHandle; // プレイヤー

	// プレイヤー
	Player* m_pPlayer;
};

