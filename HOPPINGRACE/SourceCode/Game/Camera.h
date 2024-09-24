#pragma once
#include "DxLib.h"
#include <memory>

class Player;

/// <summary>
/// �J�����N���X
/// </summary>
class Camera
{
public:
	Camera(std::shared_ptr<Player> pPlayer);
	virtual ~Camera() {};
	void Init() {};
	void Update();

	VECTOR GetPos() const { return m_pos; }		// �J�����ʒu���擾

private:
	std::shared_ptr<Player> m_pPlayer;

	VECTOR m_pos;			// �J�����ʒu

private:	// �萔
	// ����p
	static constexpr float kFov = (DX_PI_F / 180.0f) * 60.0f;
	// ��O�N���b�v����
	static constexpr float kNear = 0.1f;
	// ���N���b�v����
	static constexpr float kFar = 1000.0f;
	// �J�����̒����_
	static constexpr float kTargetX = 0.0f;		// X��
	static constexpr float kTargetY = 40.0f;	// Y��
	static constexpr float kTargetZ = -130.0f;	// Z��
};