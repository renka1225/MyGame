#pragma once
#include "DxLib.h"

class Player;

/// <summary>
/// �J�����N���X
/// </summary>
class Camera
{
public:
	Camera();
	virtual ~Camera();
	void Init();
	void Update(Player* pPlayer);

private:
	Player* m_pPlayer;

	VECTOR m_pos;
};