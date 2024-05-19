#include "Cube.h"
#include "Cube2.h"
#include "Plane.h"

/// <summary>
/// コンストラクタ
/// </summary>
Cube::Cube(std::shared_ptr<Plane> pPlane, std::shared_ptr<Cube2> pCube2):
	m_pPlane(pPlane),
	m_pCube2(pCube2),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_scale(VGet(0.05f, 0.05f, 0.05f)),
	m_angle(DX_PI_F / 180.0f),
	m_isHit(false)
{
	m_handle = MV1LoadModel("data/cube.mv1");

	MV1SetScale(m_handle, m_scale);
}


/// <summary>
/// 更新
/// </summary>
void Cube::Update()
{
	/*立方体を移動させる*/
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT))
	{
		m_pos = VAdd(m_pos, VGet(2.0f, 0.0f, 0.0f));
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT))
	{
		m_pos = VAdd(m_pos, VGet(-2.0f, 0.0f, 0.0f));
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1))
	{
		m_pos = VAdd(m_pos, VGet(0.0f, 2.0f, 0.0f));
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_2))
	{
		m_pos = VAdd(m_pos, VGet(0.0f, -2.0f, 0.0f));
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP))
	{
		m_pos = VAdd(m_pos, VGet(0.0f, 0.0f, 2.0f));
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN))
	{
		m_pos = VAdd(m_pos, VGet(0.0f, 0.0f, -2.0f));
	}

	// 表示位置更新
	MV1SetPosition(m_handle, m_pos);

	/*立方体との当たり判定*/
	//HitCube();

	/*平面との当たり判定*/
	HitPlane();
}


/// <summary>
/// 描画
/// </summary>
void Cube::Draw()
{
	MV1DrawModel(m_handle);

	if (m_isHit)
	{
		DrawString(0, 0, "当たった", 0xffffff);
	}
}


/// <summary>
/// 立方体と立方体の当たり判定
/// </summary>
void Cube::HitCube()
{
	// ターゲットとの相対ベクトルを求める
	VECTOR v3SubAbs = VSub(m_pos, m_pCube2->GetPos());

	// 相対ベクトルを絶対ベクトルに直す
	// それぞれの軸上の相対距離を成分に持つベクトルを作成
	v3SubAbs = VGet(abs(v3SubAbs.x), abs(v3SubAbs.y), abs(v3SubAbs.z));
	//v3SubAbs = VNorm(v3SubAbs);

	// それぞれの成分上での衝突距離を求める
	// 衝突距離はそれぞれの対応した辺の長さを足して2で割ったもの
	VECTOR v3AddScale = VScale(VAdd(m_scale, m_pCube2->GetScale()), 0.5f);
	// 当たり判定の範囲を広げる
	v3AddScale = VAdd(v3AddScale, VGet(14.0f, 14.0f, 14.0f));

	// デバッグ表示
	//DrawFormatString(0, 0, 0xffffff, "v3SubAbs.x:%f, v3SubAbs.y:%f, v3SubAbs.z:%f", v3SubAbs.x, v3SubAbs.y, v3SubAbs.z);
	//DrawFormatString(0, 30, 0xffffff, "v3AddScale.x:%f, v3AddScale.y:%f, v3AddScale.z:%f", v3AddScale.x, v3AddScale.y, v3AddScale.z);

	// 各成分の当たり判定
	bool isXHit = v3SubAbs.x < v3AddScale.x;
	bool isYHit = v3SubAbs.y < v3AddScale.y;
	bool isZHit = v3SubAbs.z < v3AddScale.z;

	if (isXHit && isYHit && isZHit)
	{
		m_isHit = true;
	}
	else
	{
		m_isHit = false;
	}
}


/// <summary>
/// 立方体と平面の当たり判定
/// </summary>
void Cube::HitPlane()
{
	// 外積の計算
	// 外積求めたそれぞれの成分が、面の方程式の係数になる
	// 平面の方程式 : ax + by + cz + d = 0
	VECTOR v3Normal = VCross(m_pPlane->GetV3Vec1(), m_pPlane->GetV3Vec2());
	
	// 方程式を解いて、y座標を出す式にする
	m_pos.y = (-v3Normal.x * m_pos.x - v3Normal.z * m_pos.z) / v3Normal.y + 5.0f;

	// 求めた値を代入する
	m_pos = VGet(m_pos.x, m_pos.y, m_pos.z);


	/*立方体を斜面に沿って傾ける*/
	// 基底ベクトルの作成
	// y軸
	VECTOR v3Up = VCross(m_pPlane->GetV3Vec2(), m_pPlane->GetV3Vec1());
	// 単位ベクトルにする
	v3Up = VNorm(v3Up);

	// z軸(ターゲット方向)
	VECTOR v3Forward = VGet(cosf(m_angle), 0.0f, sinf(m_angle));

	// x軸
	VECTOR v3Side = VCross(v3Up, v3Forward);
	// 単位ベクトルにする
	v3Side = VNorm(v3Side);

	// ベクトルを直交させる
	v3Forward = VCross(v3Side, v3Up);
	v3Forward = VNorm(v3Forward);

	// z軸とy軸の方向をセットする
	MV1SetRotationZYAxis(m_handle, v3Forward, v3Up, m_angle);

	// 立方体の位置を更新
	MV1SetPosition(m_handle, m_pos);
}
