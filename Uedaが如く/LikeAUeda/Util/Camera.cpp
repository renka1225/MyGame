#include "DxLib.h"
#include "Camera.h"
#include "Player.h"
#include "Input.h"
#include <cmath>

// 定数
namespace
{
	constexpr float kNear = 1.0f;							// カメラの手前クリップ距離
	constexpr float kFar = 5000.0f;							// カメラの奥クリップ距離
	constexpr float kDist = 500.0f;							// カメラからプレイヤーまでの距離
	constexpr float kHeight = 50.0f;						// カメラの注視点
	constexpr float kAngle = 0.03f;							// カメラを動かす角度
	constexpr float kInitAngleH = -DX_PI_F / 1.5f;			// カメラの初期平行角度
	constexpr float kInitAngleV = -0.5f;					// カメラの初期垂直角度
	constexpr float kMinAngleV = DX_PI_F * 0.5f - 0.6f;		// 最小の垂直角度
	constexpr float kMaxAngleV = -DX_PI_F * 0.5f + 0.6f;	// 最大の垂直角度
}

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera():
	m_pos(VGet(0.0f, kHeight, 0.0f)),
	m_target(VGet(0.0f, 0.0f, 0.0f)),
	m_angleH(kInitAngleH),
	m_angleV(kInitAngleV)
{
}


/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
	// 処理なし
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
void Camera::Update(Input& input, const Player& player)
{
	// 左入力
	if (input.IsPressing("rotateL"))
	{
		m_angleH -= kAngle;
	}
	// 右入力
	if (input.IsPressing("rotateR"))
	{
		m_angleH += kAngle;
	}
	// 上入力
	if (input.IsPressing("rotateU"))
	{
		m_angleV -= kAngle;
		// ある一定角度以上にならないようにする
		m_angleV = (std::max)(m_angleV, kMaxAngleV);
	}
	// 下入力
	if (input.IsPressing("rotateD"))
	{
		m_angleV += kAngle;
		// ある一定角度以下にならないようにする
		m_angleV = (std::min)(kMinAngleV, m_angleV);
	}

	// カメラの注視点を設定する
	m_target = VAdd(player.GetPos(), VGet(0.0f, kHeight, 0.0f));

	// カメラ位置補正
	SetCameraPositionAndTarget_UpVecY(m_pos, m_target);
}