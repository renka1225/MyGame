#pragma once

class Input;
class Player;

/// <summary>
/// �J�����N���X
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
};

