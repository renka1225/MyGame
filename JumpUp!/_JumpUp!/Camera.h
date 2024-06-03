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

private:	// �萔
	static constexpr float kNear = 1.0f;	// �J�����̎�O�N���b�v����
	static constexpr float kFar = 180.0f;	// �J�����̉��N���b�v����
	static constexpr float kDist = 96.0f;	// �J�����̋���
	static constexpr float kHeight = 32.0f;	// �J�����̍���
	static constexpr float kAngle = 0.05f;	// �J�����𓮂����p�x
};

