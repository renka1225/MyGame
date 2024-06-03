#include "DxLib.h"
#include "Camera.h"
#include "Player.h"
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
void Camera::Update(Input& input, Player& player)
{
	if (input.IsPressing("rotateL"))
	{
		m_angle += kAngle;
	}
	if (input.IsPressing("rotateR"))
	{
		m_angle -= kAngle;
	}

	// プレイヤー位置を取得
	VECTOR playerPos = player.GetPos();

	// カメラ位置調整
	m_pos.x = cosf(m_angle) * kDist + playerPos.x;
	m_pos.y = kHeight;
	m_pos.z = sinf(m_angle) * kDist + playerPos.z;
	SetCameraPositionAndTarget_UpVecY(m_pos, VGet(0, 0, 0));
}