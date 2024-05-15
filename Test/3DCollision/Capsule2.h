#pragma once
#include "DxLib.h"

// カプセル2クラス
class Capsule2
{
public:
	Capsule2();
	~Capsule2() {};
	void Draw();

	//カプセル2の中心点を取得
	VECTOR GetPos() const { return m_centerPos; }
	// カプセル2の方向ベクトルを取得
	VECTOR GetDir() const { return m_v3Direction; }

private:
	// カプセルを形成する二点中の一点の座標
	VECTOR m_pos1;
	VECTOR m_pos2;
	// カプセルの中心点
	VECTOR m_centerPos;

	// 方向ベクトル
	VECTOR m_v3Direction;
};

