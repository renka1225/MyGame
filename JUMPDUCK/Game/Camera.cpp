#include "Camera.h"
#include "Player.h"


/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera():
	m_pos(VGet(0.0f, 0.0f, 0.0f))
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
void Camera::Update(std::shared_ptr<Player> pPlayer)
{
	// プレイヤーのポインタを取得
	m_pPlayer = pPlayer;

	// カメラ位置の調整
	VECTOR aimPos = VGet(m_pPlayer->GetPos().x, kTargetY, kTargetZ);
	VECTOR posToAim = VSub(aimPos, m_pos);
	m_pos = VAdd(m_pos, posToAim);

	// カメラ位置を反映
	SetCameraScreenCenter(m_pPlayer->GetPos().x + kScreenCenterX, kScreenCenterY);
	SetCameraPositionAndTarget_UpVecY(m_pos, VGet(m_pPlayer->GetPos().x, kTargetY, 0.0f));
}