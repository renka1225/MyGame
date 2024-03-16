#include "Camera.h"
#include "Player.h"

/// <summary>
/// 定数
/// </summary>
namespace
{
	// 視野角
	constexpr float kFov = (DX_PI_F / 180.0f) * 60.0f;
	// 手前クリップ距離
	constexpr float kNear = 0.1f;
	// 奥クリップ距離
	constexpr float kFar = 1000.0f;
	// カメラの初期注視点
	constexpr float kTargetX = 0.0f;	// X軸
	constexpr float kTargetY = 80.0f;	// Y軸
	constexpr float kTargetZ = -150.0f;	// Z軸

}

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
	VECTOR aimPos = VGet(m_pPlayer->GetPos().x, kTargetY, kTargetZ);
	VECTOR posToAim = VSub(aimPos, m_pos);
	m_pos = VAdd(m_pos, posToAim);

	// カメラ位置を反映
	SetCameraPositionAndTarget_UpVecY(m_pos, VGet(m_pPlayer->GetPos().x, kTargetY, 0.0f));
}