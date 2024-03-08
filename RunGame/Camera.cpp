#include "Camera.h"
#include "Player.h"

#define DegreeToRadian (DX_PI_F / 180.0f)
float DegToRad(float degree) { return (DegreeToRadian * degree); }

Camera::Camera(Player* pPlayer):
	m_pPlayer(pPlayer),
	m_pos(VGet(0, 20, -30))
{
	// 視野角の設定
	SetupCamera_Perspective(DegToRad(60.0f));
	// カメラの描画範囲
	SetCameraNearFar(0.1f, 1000.0f);
	// カメラを接地
	SetCameraPositionAndTarget_UpVecY(VGet(0, 10, -20), VGet(0.0f, 10.0f, 0.0f));
}

Camera::~Camera()
{
	// 処理なし
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