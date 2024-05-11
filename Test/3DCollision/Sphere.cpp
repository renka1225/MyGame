#include "Sphere.h"
#include <cmath>

Sphere::Sphere() :
	m_pos(VGet(200.0f, 100.0f, 0.0f)),
	m_targetSpherePos(VGet(500.0f, 300.0f, 0.0f)),
	m_cupsulePos1(VGet(800.0f, 100.0f, 0.0f)),
	m_cupsulePos2(VGet(900.0f, 200.0f, 10.0f)),
	m_isHit(false)
{
}

Sphere::~Sphere()
{
}

void Sphere::Init()
{
}

void Sphere::Update()
{
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		m_pos.x += 10.0f;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		m_pos.x -= 10.0f;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		m_pos.y += 10.0f;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		m_pos.y -= 10.0f;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		m_pos.z += 10.0f;
	}
	if (CheckHitKey(KEY_INPUT_Z))
	{
		m_pos.z -= 10.0f;
	}

	// 球との当たり判定
	HitSphere();
	// カプセルとの当たり判定
	//HitCupsule();
}

void Sphere::Draw()
{
	// 球を描画する
	DrawSphere3D(m_targetSpherePos, kRadius, kDivNum, 0xffffff, 0xffffff, true);
	// カプセルを描画する
	DrawCapsule3D(m_cupsulePos1, m_cupsulePos2, kCupsuleRadius, 8, 0xffffff, 0xffffff, true);

	// 当たっている時は球の色を変える
	int color = 0x0000ff;
	if (m_isHit)
	{
		color = 0xff0000;
	}

	DrawSphere3D(m_pos, kRadius, kDivNum, color, 0xffffff, true);
}


/// <summary>
/// 球との当たり判定
/// </summary>
void Sphere::HitSphere()
{
	// 相対ベクトルを計算
	VECTOR v3Delta = VSub(m_pos, m_targetSpherePos);
	// マグニチュード
	float fDistanceSq = v3Delta.x * v3Delta.x + v3Delta.y * v3Delta.y + v3Delta.z * v3Delta.z;

	// マグニチュードが半径の2乗未満の場合当たってる
	if (fDistanceSq < ((kRadius + kRadius) * (kRadius + kRadius)))
	{
		m_isHit = true;
	}
	else
	{
		m_isHit = false;
	}
}


/// <summary>
/// カプセルとの当たり判定
/// </summary>
void Sphere::HitCupsule()
{
	// 点1から点2に向かう単位ベクトルを計算
	VECTOR direction = VSub(m_cupsulePos2, m_cupsulePos1);

	// 点1から球の中心への相対ベクトルを計算
	VECTOR v3Delta = VSub(m_pos, m_cupsulePos1);

	// 衝突する物体の正面ベクトルと相対ベクトルの内積を求める
	// 点1から点2を線上に球の中心から垂線を下ろした時の点が求められる
	float dot = VDot(direction, v3Delta);

	// 衝突物体の正面ベクトルのマグニチュード
	float mag = VSize(v3Delta);

	// 点に向かう法線ベクトル(垂線)を求める
	float t = dot / mag;

	// 線分と点の距離を求めるためのtの制限
	if (t < -1.0f) t = -1.0f; // tの下限
	if (t > 1.0f) t = 1.0f;   // tの上限

	// p = at + c(c:線分の中点)で点との最短距離になるカプセル上の点の位置を求める
	//VECTOR v3MinPos = VAdd(VGet(cupsulePos.x * t, cupsulePos.y * t, cupsulePos.z * t), cupsulePos);   // 最小位置を与える座標
	direction = VGet(direction.x * t, direction.y * t, direction.z * t);
	VECTOR v3MinPos = VAdd(m_pos, direction);   // 最小位置を与える座標

	// pと球との距離のマグニチュード
	float fDistSqr = VSize(VSub(v3MinPos, m_pos));

	// 衝突距離の計算
	float ar = kRadius + kCupsuleRadius;

	// 当たり判定(2乗のまま比較)
	if (fDistSqr < (ar * ar))
	{
		m_isHit = true;
	}
	else
	{
		m_isHit = false;
	}
}
