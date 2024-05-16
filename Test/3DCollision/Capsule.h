#pragma once
#include "DxLib.h"
#include <memory>

class Capsule2;

// カプセル1クラス
class Capsule
{
public:
	Capsule(std::shared_ptr<Capsule2> pCapsule2);
	~Capsule() {};
	void Update();
	void Draw();
	void HitCapsule();	// カプセルとカプセルの当たり判定

private:
	std::shared_ptr<Capsule2> m_pCapsule2;

	// カプセルを形成する二点中の一点の座標
	VECTOR m_pos1;
	VECTOR m_pos2;
	// カプセルの中心点
	VECTOR m_centerPos;
	// 方向ベクトル
	VECTOR m_v3Direction;
	// カプセルの幅
	float m_radius;
	// カプセルの色
	int m_color;
	// 球の色
	bool m_isHit;

	// VECTOR4の構造体
	struct VECTOR4
	{
		float x, y, z, w;
	};

	// VECTOR4の積を計算
	float VECTOR4Dot(VECTOR4 a, VECTOR4 b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	// 行列の行を取得する
	VECTOR4 GetRow(MATRIX mat, int row)
	{
		return VECTOR4{ mat.m[row][0], mat.m[row][1], mat.m[row][2], mat.m[row][3] };
	}

private:
	static constexpr float kRadius = 10.0f;	// カプセルの幅
};

