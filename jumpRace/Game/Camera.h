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
	Camera(std::shared_ptr<Player> pPlayer);
	virtual ~Camera() {};
	void Init() {};
	void Update();

	VECTOR GetPos() const { return m_pos; }		// カメラ位置を取得

private:
	std::shared_ptr<Player> m_pPlayer;

	VECTOR m_pos;			// カメラ位置

private:	// 定数
	// 視野角
	static constexpr float kFov = (DX_PI_F / 180.0f) * 60.0f;
	// 手前クリップ距離
	static constexpr float kNear = 0.1f;
	// 奥クリップ距離
	static constexpr float kFar = 1000.0f;
	// カメラの注視点
	static constexpr float kTargetX = 0.0f;		// X軸
	static constexpr float kTargetY = 40.0f;	// Y軸
	static constexpr float kTargetZ = -130.0f;	// Z軸
};