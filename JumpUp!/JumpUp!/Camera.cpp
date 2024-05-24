#include "DxLib.h"
#include "Camera.h"
#include "Input.h"
#include <cmath>

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera():
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_angle(-DX_PI_F / 2)
{
}


/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
}


/// <summary>
/// 初期化
/// </summary>
void Camera::Init()
{
	SetCameraNearFar(kNear, kFar);
}


/// <summary>
/// 更新
/// </summary>
void Camera::Update(Input& input)
{
	if (input.IsPressing("rotateL"))
	{
		m_angle += kAngle;
	}
	if (input.IsPressing("rotateR"))
	{
		m_angle -= kAngle;
	}

	m_pos.x = cosf(m_angle) * kDist;
	m_pos.y = kHeight;
	m_pos.z = sinf(m_angle) * kDist;
	SetCameraPositionAndTarget_UpVecY(m_pos, VGet(0, 0, 0));
}