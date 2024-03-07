#include "Camera.h"
#include "Player.h"

#define DegreeToRadian (DX_PI_F / 180.0f)
float DegToRad(float degree) { return (DegreeToRadian * degree); }

Camera::Camera(Player* pPlayer):
	m_pPlayer(pPlayer),
	m_pos(VGet(0, 20, -30))
{
	SetupCamera_Perspective(DegToRad(60.0f));
}

/// <summary>
/// 初期化
/// </summary>
void Camera::Init()
{
}


/// <summary>
/// 更新
/// </summary>
void Camera::Update()
{
}