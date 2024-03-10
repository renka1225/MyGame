#pragma once
#include "DxLib.h"
#include <memory>

class Player;

/// <summary>
/// ƒJƒƒ‰ƒNƒ‰ƒX
/// </summary>
class Camera
{
public:
	Camera();
	virtual ~Camera();
	void Init();
	void Update(std::shared_ptr<Player> pPlayer);

private:
	std::shared_ptr<Player> m_pPlayer;

	VECTOR m_pos;
};