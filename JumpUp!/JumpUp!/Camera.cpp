#include "DxLib.h"
#include "Camera.h"
#include "Player.h"
#include "Stage.h"
#include "Input.h"
#include <cmath>

// 定数
namespace
{
	constexpr float kNear = 1.0f;							// カメラの手前クリップ距離
	constexpr float kFar = 5000.0f;							// カメラの奥クリップ距離
	constexpr float kDist = 150.0f;							// カメラからプレイヤーまでの距離
	constexpr float kHeight = 60.0f;						// カメラの注視点
	constexpr float kAngle = 0.03f;							// カメラを動かす角度
	constexpr float kInitAngleH = -DX_PI_F / 1.5f;			// カメラの初期平行角度
	constexpr float kInitAngleV = -0.3f;					// カメラの初期垂直角度
	constexpr float kMinAngleV = DX_PI_F * 0.5f - 0.6f;		// 最小の垂直角度
	constexpr float kMaxAngleV = -DX_PI_F * 0.5f + 0.6f;	// 最大の垂直角度
	constexpr float kColSize = 3.0f;						// カメラの当たり判定サイズ
	constexpr float kHitLength = 0.1f;						// カメラがステージに当たったか判定する距離
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

	// カメラの座標を求める
	// X軸にカメラからプレイヤーまでの距離分伸びたベクトルを垂直方向に回転する(Z軸回転)
	m_pos = VTransform(VGet(-kDist, 0.0f, 0.0f), rotZ);
	// 水平方向(Y軸回転)に回転する
	m_pos = VTransform(m_pos, rotY);
	// 注視点の座標を足す
	m_pos = VAdd(m_pos, m_target);

	// 注視点からカメラの座標までの間にステージのポリゴンがあるか調べる
	float notHitLength = 0.0f;	// ポリゴンに当たらない距離
	float hitLength = kDist;	// ポリゴンに当たる距離

	do
	{
		// カメラがステージに当たるかテストする距離
		// 当たらない距離と当たる距離の中間を求める
		float testLength = notHitLength + (hitLength - notHitLength) * 0.5f;
		// 次のフレームのカメラ座標を求める
		auto nextPos = VTransform(VGet(-testLength, 0.0f, 0.0f), rotZ);
		nextPos = VTransform(nextPos, rotY);
		nextPos = VAdd(nextPos, m_target);

		// 新しい座標で壁に当たるかテストする
		auto hitResult = MV1CollCheck_Capsule(stage.GetStageHandle(), -1, m_target, nextPos, kColSize);
		int hitNum = hitResult.HitNum;
		MV1CollResultPolyDimTerminate(hitResult);

		// 当たった場合
		if (hitNum != 0)
		{
			// 当たる距離をtestLenthに変更する
			hitLength = testLength;
			// カメラ座標を更新
			m_pos = nextPos;
		}
		else
		{
			// 当たらない距離をtestLenthに変更する
			notHitLength = testLength;
		}
	} while (hitLength - notHitLength > kHitLength); // hitLengthとNoHitLengthが十分に近づいていない場合ループする

}
