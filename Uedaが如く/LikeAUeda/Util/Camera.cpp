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
	constexpr float kDist = 100.0f;							// カメラからプレイヤーまでの距離
	constexpr float kHeight = 60.0f;						// カメラの注視点
	constexpr float kAngle = 0.03f;							// カメラを動かす角度
	constexpr float kInitAngleH = -DX_PI_F / 2.0f;			// カメラの初期平行角度
	constexpr float kInitAngleV = -0.3f;					// カメラの初期垂直角度
	constexpr float kMinAngleV = DX_PI_F * 0.5f - 1.0f;		// 最小の垂直角度
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
	AnalogInput.Rx = 0;
	AnalogInput.Ry = 0;
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
	GetJoypadDirectInputState(DX_INPUT_PAD1, &AnalogInput); // 入力状態を取得

	// 左入力
	if (AnalogInput.Rx < 0.0f || input.IsPressing("rotateL"))
	{
		m_angleH -= kAngle;
	}
	// 右入力
	if (AnalogInput.Rx > 0.0f || input.IsPressing("rotateR"))
	{
		m_angleH += kAngle;
	}
	// 上入力
	if (AnalogInput.Ry > 0.0f || input.IsPressing("rotateU"))
	{
		m_angleV -= kAngle;
		// ある一定角度以上にならないようにする
		m_angleV = std::max(m_angleV, kMaxAngleV);
	}
	// 下入力
	if (AnalogInput.Ry < 0.0f || input.IsPressing("rotateD"))
	{
		m_angleV += kAngle;
		// ある一定角度以下にならないようにする
		m_angleV = std::min(kMinAngleV, m_angleV);
	}

	// カメラの注視点を設定する
	m_target = VAdd(player.GetPos(), VGet(0.0f, kHeight, 0.0f));

	// カメラ位置補正
	FixCameraPos();
	SetCameraPositionAndTarget_UpVecY(m_pos, m_target);
}

/// <summary>
/// カメラ位置を補正する
/// </summary>
void Camera::FixCameraPos()
{
	// 水平方向の回転
	auto rotY = MGetRotY(m_angleH);
	// 垂直方向の回転
	auto rotZ = MGetRotZ(m_angleV);

	// カメラの座標を求める
	// X軸にカメラからプレイヤーまでの距離分伸びたベクトルを垂直方向に回転する(Z軸回転)
	m_pos = VTransform(VGet(-kDist, 0.0f, 0.0f), rotZ);
	// 水平方向(Y軸回転)に回転する
	m_pos = VTransform(m_pos, rotY);
	// 注視点の座標を足す
	m_pos = VAdd(m_pos, m_target);
}
