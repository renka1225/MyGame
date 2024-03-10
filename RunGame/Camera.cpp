#include "Camera.h"
#include "Player.h"

#define DegreeToRadian (DX_PI_F / 180.0f)
float DegToRad(float degree) { return (DegreeToRadian * degree); }

Camera::Camera():
	m_pos(VGet(0, 20, -30))
{
	// 視野角の設定
	SetupCamera_Perspective(DegToRad(60.0f));
	// カメラの描画範囲
	SetCameraNearFar(0.1f, 1000.0f);
	// カメラを設置
	SetCameraPositionAndTarget_UpVecY(VGet(0, 50, -100), VGet(0.0f, 17.0f, 0.0f));
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
void Camera::Update(std::shared_ptr<Player> pPlayer)
{
	// プレイヤーのポインタを取得
	m_pPlayer = pPlayer;

	// カメラ位置の調整
	VECTOR aimPos = VGet(m_pPlayer->GetPos().x, 0.0f, -200.0f);
	VECTOR posToAim = VSub(aimPos, m_pos);
	VECTOR scaledPosToAim = VScale(posToAim, 0.1f);
	m_pos = VAdd(m_pos, scaledPosToAim);

	// カメラ位置を反映
	SetCameraPositionAndTarget_UpVecY(m_pos, m_pPlayer->GetPos());
}