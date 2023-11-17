#pragma once
#include <vector>
#include "Vec2.h"

class Player;

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
	int m_playerHandle;

	// プレイヤー
	Player* m_pPlayer;
};

