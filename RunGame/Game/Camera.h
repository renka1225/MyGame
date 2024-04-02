#pragma once
#include "DxLib.h"
#include <memory>

class Player;

/// <summary>
/// カメラクラス
/// </summary>
class Camera
{
public:
	Camera();
	virtual ~Camera();
	void Init();
	void Update(std::shared_ptr<Player> pPlayer);

	VECTOR GetPos() const { return m_pos; }		// カメラ位置を取得

private:
	std::shared_ptr<Player> m_pPlayer;

	VECTOR m_pos;
};