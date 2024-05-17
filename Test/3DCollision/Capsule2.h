#pragma once
#include "DxLib.h"

// カプセル2クラス
class Capsule2
{
public:
	Capsule2();
	~Capsule2() {};
	void Draw();

	// カプセル2の始点を取得
	VECTOR GetPos1() const { return m_pos1; }
	// カプセル2の終点を取得
	VECTOR GetPos2() const { return m_pos2; }
	// カプセル2の方向ベクトルを取得
	VECTOR GetDir() const { return m_v3Direction; }
	//カプセル2の中心点を取得
	VECTOR GetPos() const { return m_centerPos; }
	// カプセル2の幅を取得
	float GetRadius() const { return m_radius; }

private:
	// カプセルを形成する二点中の一点の座標
	VECTOR m_pos1;
	VECTOR m_pos2;
	// 方向ベクトル
	VECTOR m_v3Direction;
	// カプセルの中心点
	VECTOR m_centerPos;
	// カプセルの幅
	float m_radius;

private:
	static constexpr float kRadius = 10.0f;	// カプセルの幅
};

