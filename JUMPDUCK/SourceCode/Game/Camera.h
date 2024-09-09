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
	Camera();
	virtual ~Camera() {};
	void Init() {};
	void Update(std::shared_ptr<Player> pPlayer);

	VECTOR GetPos() const { return m_pos; }		// �J�����ʒu���擾

private:
	std::shared_ptr<Player> m_pPlayer;

	VECTOR m_pos;

private:	// �萔
	// ����p
	static constexpr float kFov = (DX_PI_F / 180.0f) * 60.0f;
	// ��O�N���b�v����
	static constexpr float kNear = 0.1f;
	// ���N���b�v����
	static constexpr float kFar = 1000.0f;
	// �J�����̏��������_
	static constexpr float kTargetX = 0.0f;		// X��
	static constexpr float kTargetY = 50.0f;	// Y��
	static constexpr float kTargetZ = -100.0f;	// Z��
	// �J�����̒��S���W
	static constexpr float kScreenCenterX = 300.0f;	// X���W
	static constexpr float kScreenCenterY = 500.0f;	// Y���W
};