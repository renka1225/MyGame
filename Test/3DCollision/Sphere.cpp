#include "Sphere.h"
#include "Sphere2.h"
#include "Capsule2.h"
#include "Triangle.h"

/// <summary>
/// コンストラクタ
/// </summary>
Sphere::Sphere(std::shared_ptr<Sphere2> pSphere2, std::shared_ptr<Capsule2> pCapsule2, std::shared_ptr<Triangle> pTriangle):
	m_pSphere2(pSphere2),
	m_pCapsule2(pCapsule2),
	m_pTriangle(pTriangle),
	m_pos(VGet(-30.0f, 0.0f, 0.0f)),
	m_radius(kRadius),
	m_color(-1),
	m_isHit(false)
{
}


/// <summary>
/// 更新
/// </summary>
void Sphere::Update()
{
	/*球を移動させる*/
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

	/*球との当たり判定*/
	//HitSphere();

	/*カプセルとの当たり判定*/
	//HitCapsule();
	
	/*三角形との当たり判定*/
	//HitTriangle();
}


/// <summary>
/// 描画
/// </summary>
void Sphere::Draw()
{
	if (m_isHit)
	{
		m_color = 0xff0000;
	}
	else
	{
		m_color = 0x0000ff;
	}

	DrawSphere3D(m_pos, m_radius, 8, m_color, 0x000000, true);
}


/// <summary>
/// 球と球の当たり判定
/// </summary>
void Sphere::HitSphere()
{
	// 球2の座標を取得
	VECTOR sphere2Pos = m_pSphere2->GetPos();

	// 相対ベクトル
	VECTOR v3Delta = VSub(m_pos, sphere2Pos);

	// マグニチュード
	float fDistanceSq = VSquareSize(v3Delta);

	// 当たり判定
	// それぞれの半径を足した2乗
	if (fDistanceSq < (m_radius + 10.0f) * (m_radius + 10.0f))
	{
		m_isHit = true;
	}
	else
	{
		m_isHit = false;
	}
}


/// <summary>
/// 球とカプセルの当たり判定
/// </summary>
void Sphere::HitCapsule()
{
	// カプセル2の中心座標を取得
	VECTOR capsule2Pos = m_pCapsule2->GetPos();
	// カプセル2の正面ベクトルを取得
	VECTOR capsule2V3Dir = m_pCapsule2->GetDir();

	// 相対ベクトル
	// 終点から始点を引く
	VECTOR v3DeltaPos = VSub(capsule2Pos, m_pos);

	// カプセルの正面ベクトルと相対ベクトルの内積
	float dot = VDot(capsule2V3Dir, v3DeltaPos);

	// カプセルの正面ベクトルのマグニチュード
	float mag = VSquareSize(capsule2V3Dir);

	// tは点に向かう法線ベクトル(垂線)を求めるための係数
	float t = dot / mag;

	// 線分と点の距離を求めるためのtの制限
	if (t < -1.0f) t = -1.0f;   // tの下限
	if (t > 1.0f) t = 1.0f;   // tの上限

	// p = at + c(c:線分の中点)で点との最短距離になる線分上の点の位置を求める
	VECTOR v3MinPos = VAdd(VScale(capsule2V3Dir, t), capsule2Pos);   // 最小位置を与える座標

	// pと自分との距離のマグニチュード
	float fDistSqr = VSquareSize(VSub(m_pos, v3MinPos));

	// 衝突距離の計算
	// 球の半径とカプセルの幅を足す
	float ar = kRadius + m_pCapsule2->GetRadius();

	// 当たり判定(2乗のまま比較)
	if (fDistSqr < ar * ar)
	{                       
		m_isHit = true;
	}
	else
	{
		// 端の円の部分との判定
		// カプセルの端の位置を計算
		VECTOR capsule2Pos1 = m_pCapsule2->GetPos1();
		VECTOR capsule2Pos2 = m_pCapsule2->GetPos2();
		float distSqrToEnd1 = VSquareSize(VSub(m_pos, capsule2Pos1));
		float distSqrToEnd2 = VSquareSize(VSub(m_pos, capsule2Pos2));

		if (distSqrToEnd1 < ar * ar || distSqrToEnd2 < ar * ar)
		{
			m_isHit = true;
		}
		else
		{
			m_isHit = false;
		}
	}
}


/// <summary>
/// 球と三角形の当たり判定
/// </summary>
void Sphere::HitTriangle()
{
	VECTOR v3TriVec0, v3TriVec1, v3TriVec2;
	VECTOR v3HitVec0, v3HitVec1, v3HitVec2;
	float fCross0, fCross1, fCross2;
	
	// 三角形サイクルベクトル
	v3TriVec0 = VSub(m_pTriangle->GetPos2(), m_pTriangle->GetPos1());
	v3TriVec1 = VSub(m_pTriangle->GetPos3(), m_pTriangle->GetPos2());
	v3TriVec2 = VSub(m_pTriangle->GetPos1(), m_pTriangle->GetPos3());

	// 三角形頂点からターゲットへのベクトル
	v3HitVec0 = VSub(m_pos, m_pTriangle->GetPos1());
	v3HitVec1 = VSub(m_pos, m_pTriangle->GetPos2());
	v3HitVec2 = VSub(m_pos, m_pTriangle->GetPos3());

	// それぞれの外積
	fCross0 = v3TriVec0.z * v3HitVec0.x - v3TriVec0.x * v3HitVec0.z;
	fCross1 = v3TriVec1.z * v3HitVec1.x - v3TriVec1.x * v3HitVec1.z;
	fCross2 = v3TriVec2.z * v3HitVec2.x - v3TriVec2.x * v3HitVec2.z;

	// 当たっているかのフラグ変数
	bool bHit = false;

	// 全て同じ側にいるかの判定
	if (fCross0 >= 0.0f)
	{
		if ((fCross1 >= 0.0f) && (fCross2 >= 0.0f))
		{
			bHit = true;
		}
	}
	else
	{
		if ((fCross1 < 0.0f) && (fCross2 < 0.0f))
		{
			bHit = true;
		}
	}

	// 当たっていた時の処理
	if (bHit)
	{
		m_isHit = true;
	}
	else
	{
		m_isHit = false;
	}
}
