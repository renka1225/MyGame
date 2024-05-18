#include "Capsule.h"
#include "Capsule2.h"

/// <summary>
/// コンストラクタ
/// </summary>
Capsule::Capsule(std::shared_ptr<Capsule2> pCapsule2):
	m_pCapsule2(pCapsule2),
	m_pos1(VGet(0.0f, 0.0f, 0.0f)),
	m_pos2(VGet(-30.0f, 0.0f, 10.0f)),
	m_centerPos(VScale(VAdd(m_pos1, m_pos2), 0.5f)),
	m_v3Direction(VSub(m_pos2, m_pos1)),
	m_radius(kRadius),
	m_color(-1),
	m_isHit(false)
{
}


/// <summary>
/// 更新
/// </summary>
void Capsule::Update()
{
	/*カプセルを移動させる*/
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_RIGHT))
	{
		m_centerPos = VAdd(m_centerPos, VGet(2.0f, 0.0f, 0.0f));
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_LEFT))
	{
		m_centerPos = VAdd(m_centerPos, VGet(-2.0f, 0.0f, 0.0f));
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1))
	{
		m_centerPos = VAdd(m_centerPos, VGet(0.0f, 2.0f, 0.0f));
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_2))
	{
		m_centerPos = VAdd(m_centerPos, VGet(0.0f, -2.0f, 0.0f));
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_UP))
	{
		m_centerPos = VAdd(m_centerPos, VGet(0.0f, 0.0f, 2.0f));
	}
	if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_DOWN))
	{
		m_centerPos = VAdd(m_centerPos, VGet(0.0f, 0.0f, -2.0f));
	}

	// カプセルの座標を更新
	m_pos1 = VSub(m_centerPos, VGet(0.0f, 0.0f, 0.0f));
	m_pos2 = VAdd(m_centerPos, VGet(-30.0f, 0.0f, 10.0f));

	/*カプセルとの当たり判定*/
	HitCapsule();
}

/// <summary>
/// 描画
/// </summary>
void Capsule::Draw()
{
	if (m_isHit)
	{
		m_color = 0xff0000;
	}
	else
	{
		m_color = 0x0000ff;
	}

	// カプセルを描画
	DrawCapsule3D(m_pos1, m_pos2, m_radius, 8, m_color, 0x000000, true);
}


/// <summary>
/// カプセルとの当たり判定
/// </summary>
void Capsule::HitCapsule()
{
	// 計算用の変数
	float s,t;

	// ターゲットと自分の相対ベクトルを作成
	VECTOR v3DeltaPos = VSub(m_pCapsule2->GetPos(), m_centerPos);
	// 行列の掛け算ができるように4つ目の要素を増やす
	VECTOR4 v4DeltaPos = { v3DeltaPos.x, v3DeltaPos.y, v3DeltaPos.z, 0.0f };

	// お互いの方向ベクトルの外積をして法線ベクトルを出す
	VECTOR v3Normal = VCross(m_pCapsule2->GetDir(), m_v3Direction);

	// 平行状態かを判定する
	bool bParallel = false;

	// 法線ベクトルの大きさがある一定より小さい場合、平行状態
	if (VSquareSize(v3Normal) < 0.001f)
	{
		bParallel = true;
	}
	
	// 平行か平行でないかの計算
	if (!bParallel) // 平行でない 
	{
		// 4*4の単位行列を作成
		MATRIX matSolve = MGetIdent();

		// 単位行列に数値を入れる
		// 1列目:自分のベクトル
		matSolve.m[0][0] = m_v3Direction.x;
		matSolve.m[1][0] = m_v3Direction.y;
		matSolve.m[2][0] = m_v3Direction.z;
		matSolve.m[3][0] = 0.0f;

		// 2列目:ターゲットの方向ベクトルを反転させたもの
		matSolve.m[0][1] = -m_pCapsule2->GetDir().x;
		matSolve.m[1][1] = -m_pCapsule2->GetDir().y;
		matSolve.m[2][1] = -m_pCapsule2->GetDir().z;
		matSolve.m[3][1] = 0.0f;

		// 3つ目:互いの法線ベクトル(外積)
		matSolve.m[0][2] = v3Normal.x;
		matSolve.m[1][2] = v3Normal.y;
		matSolve.m[2][2] = v3Normal.z;
		matSolve.m[3][2] = 0.0f;

		// 逆行列にする
		matSolve = MInverse(matSolve);

		// 行列の計算
		// 行を取得
		VECTOR4 row0 = GetRow(matSolve, 0);
		VECTOR4 row1 = GetRow(matSolve, 1);

		// パラメータsを出す
		s = VECTOR4Dot(row0, v4DeltaPos);
		// パラメータtを出す
		t = VECTOR4Dot(row1, v4DeltaPos);
	}
	else // 平行
	{
		s = VDot(m_v3Direction, v3DeltaPos) / VSquareSize(m_v3Direction);
		t = VDot(m_pCapsule2->GetDir(), VScale(v3DeltaPos, -1)) / VSquareSize(m_pCapsule2->GetDir());
	}

	//排他条件処理
	if (s < 0.0f) s = 0.0f; // sの下限
	if (s > 1.0f) s = 1.0f; // sの上限
	if (t < 0.0f) t = 0.0f; // tの下限
	if (t > 1.0f) t = 1.0f; // tの上限

	// サイズ調整された自分の方向ベクトルと自分の座標の相対ベクトル(加算)を出す
	VECTOR v3MinPos1 = VAdd(VScale(m_v3Direction, s), m_centerPos);
	// サイズ調整されたターゲットの方向ベクトルとターゲットの座標の相対ベクトル(加算)を出す
	VECTOR v3MinPos2 = VAdd(VScale(m_pCapsule2->GetDir(), t), m_pCapsule2->GetPos());

	// 上記の相対ベクトルのマグニチュード
	float fDistSqr = VSquareSize(VSub(v3MinPos1, v3MinPos2));

	// 自分とターゲットの半径の合計
	float ar = m_pCapsule2->GetRadius() + m_radius;

	// 相対ベクトルと半径の合計の比較(マグニチュードのまま計算する)
	if (fDistSqr < ar * ar) // 半径の合計より小さい時
	{
		if (!bParallel)
		{
			m_isHit = true;
		}
		else
		{
			m_isHit = false;
		}
	}
	else // 半径の合計より大きい時
	{
		if (!bParallel)
		{
			m_isHit = false;
		}
		else
		{
			m_isHit = false;
		}
	}
}
