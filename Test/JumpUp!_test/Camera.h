#pragma once

class Input;
class Player;

/// <summary>
/// カメラクラス
/// </summary>
class Camera
{
public:
	Camera();
	~Camera();
	void Init();
	void Update(Input& input, Player& player);

	float GetAngle() const { return m_angle; }

private:

	VECTOR m_pos;
	float m_angle;

private:	// 定数
	static constexpr float kNear = 1.0f;	// カメラの手前クリップ距離
	static constexpr float kFar = 180.0f;	// カメラの奥クリップ距離
	static constexpr float kDist = 96.0f;	// カメラの距離
	static constexpr float kHeight = 32.0f;	// カメラの高さ
	static constexpr float kAngle = 0.05f;	// カメラを動かす角度
};

