#pragma once
#include "DxLib.h"

class Player;

/// <summary>
/// ƒJƒƒ‰ƒNƒ‰ƒX
/// </summary>
class Camera
{
public:
	Camera(Player* pPlayer);
	virtual ~Camera();
	void Init();
	void Update();

private:
	Player* m_pPlayer;
	VECTOR m_pos;
};