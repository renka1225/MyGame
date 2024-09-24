#pragma once

class Input;
class Player;
class Stage;

/// <summary>
/// カメラクラス
/// </summary>
class Camera
{
public:
	Camera();
	~Camera();
	void Init();
	void Update(Input& input, const Player& player, const Stage& stage);

	VECTOR GetAngle() const { return m_target; }
	VECTOR GetPos() const { return m_pos; }

private:
	void FixCameraPos(const Stage& stage);	// カメラ位置補正

private:
	VECTOR m_pos;	 // カメラ座標
	VECTOR m_target; // 注視点座標
	float m_angleH;	 // 水平角度
	float m_angleV;	 // 垂直角度
};

