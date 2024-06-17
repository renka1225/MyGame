#include "DxLib.h"
#include "Camera.h"
#include "Player.h"
#include "Input.h"
#include <cmath>

// 定数
namespace
{
	constexpr float kNear = 1.0f;							// カメラの手前クリップ距離
	constexpr float kFar = 1000.0f;							// カメラの奥クリップ距離
	constexpr float kDist = 96.0f;							// カメラの距離
	constexpr float kHeight = 40.0f;						// カメラの注視点
	constexpr float kAngle = 0.03f;							// カメラを動かす角度
	constexpr float kMinAngleV = DX_PI_F * 0.5f - 0.6f;		// 最小の垂直角度
	constexpr float kMaxAngleV = -DX_PI_F * 0.5f + 0.6f;	// 最大の垂直角度
}

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera():
	m_pos(VGet(0.0f, kHeight, 0.0f)),
	m_target(VGet(0.0f, 0.0f, 0.0f)),
	m_angleH(-DX_PI_F / 2),
	m_angleV(0.0f)
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
void Camera::Update(Input& input, const Player& player, const Stage& stage)
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
		m_angleV = std::max(m_angleV, kMaxAngleV);
	}
	// 下入力
	if (input.IsPressing("rotateD"))
	{
		m_angleV += kAngle;
		// ある一定角度以下にならないようにする
		m_angleV = std::min(kMinAngleV, m_angleV);
	}

	// カメラの注視点を設定する
	m_target = VAdd(player.GetPos(), VGet(0.0f, kHeight, 0.0f));

	// カメラ位置補正
	FixCameraPos(stage);
	SetCameraPositionAndTarget_UpVecY(m_pos, m_target);
}


/// <summary>
/// カメラ位置を補正する
/// </summary>
void Camera::FixCameraPos(const Stage& stage)
{
	// 水平方向の回転
	auto rotY = MGetRotY(m_angleH);
	// 垂直方向の回転
	auto rotZ = MGetRotZ(m_angleV);

	// カメラからプレイヤーまでの距離をセットする
	float cameraToPlayerLength = kDist;

	// カメラの座標を求める
	// 1.X軸にカメラからプレイヤーまでの距離分伸びたベクトルを垂直方向に回転する(Z軸回転)
	// 2.水平方向(Y軸回転)に回転する
	// 3.注視点の座標を足す
	m_pos = VAdd(VTransform(VTransform(VGet(-cameraToPlayerLength, 0.0f, 0.0f), rotZ), rotY), m_target);

	// 注視点からカメラの座標までの間にステージのポリゴンがあるか調べる
	float notHitLength = 0.0f;				// ポリゴンに当たらない距離
	float hitLength = cameraToPlayerLength;	// ポリゴンに当たる距離
	// 当たるかどうか
	float testLength = notHitLength + (hitLength - notHitLength) * 0.5f;
	// テスト用のカメラ座標を算出
	auto testPosition = VAdd(VTransform(VTransform(VGet(-testLength, 0.0f, 0.0f), rotZ), rotY), m_target);
}
