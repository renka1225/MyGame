#include "Camera.h"
#include "Player.h"


/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera(std::shared_ptr<Player> pPlayer):
	m_pPlayer(pPlayer),
	m_pos(VGet(0.0f, 0.0f, m_pPlayer->GetPos().z + kTargetZ))
{
	// 視野角の設定
	SetupCamera_Perspective(kFov);
	// カメラの描画範囲
	SetCameraNearFar(kNear, kFar);
	// カメラを設置
	SetCameraPositionAndTarget_UpVecY(m_pos, VGet(0.0f, kTargetY, 0.0f));
}


/// <summary>
/// 更新
/// </summary>
void Camera::Update()
{
	// カメラ位置の調整
	VECTOR aimPos = VGet(kTargetX, kTargetY, m_pPlayer->GetPos().z + kTargetZ);
	VECTOR posToAim = VSub(aimPos, m_pos);
	m_pos = VAdd(m_pos, posToAim);

	// カメラ位置を反映
	SetCameraPositionAndTarget_UpVecY(m_pos, VGet(kTargetX, kTargetY, 0.0f));
}
