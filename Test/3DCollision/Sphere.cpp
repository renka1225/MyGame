#include "Sphere.h"

Sphere::Sphere() :
	m_pos(VGet(200.0f, 100.0f, 0.0f)),
	m_targetPos(VGet(500.0f, 300.0f, 0.0f))
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

	// 相対ベクトルを計算
	VECTOR v3Delta = VSub(m_pos, m_targetPos);
	// マグニチュード
	float fDistanceSq = v3Delta.x * v3Delta.x + v3Delta.y * v3Delta.y + v3Delta.z * v3Delta.z;

	// 当たり判定
	// マグニチュードが直径の2乗未満の場合当たってる
	if (fDistanceSq < (kRadius * kRadius * 4))
	{
		m_isHit = true;
	}
	else
	{
		m_isHit = false;
	}
}

void Sphere::Draw()
{
	//球を描画する
	DrawSphere3D(m_targetPos, kRadius, kDivNum, 0xffffff, 0xffffff, true);

	// 当たっている時は球の色を変える
	int color = 0x0000ff;
	if (m_isHit)
	{
		color = 0xff0000;
	}

	DrawSphere3D(m_pos, kRadius, kDivNum, color, 0xffffff, true);
}
