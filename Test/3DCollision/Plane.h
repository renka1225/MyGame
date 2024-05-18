#pragma once
#include "DxLib.h"

// 平面クラス
class Plane
{
public:
	Plane();
	~Plane() {};
	void Update();
	void Draw();

	// 平面のX方向の傾斜を取得
	VECTOR GetV3Vec1() const { return m_v3Vec1; }
	// 平面のY方向の傾斜を取得
	VECTOR GetV3Vec2() const { return m_v3Vec2; }

private:
	// 頂点データ
	VERTEX3D Vertex[4];
	WORD Index[6];

	// X方向の傾斜
	VECTOR m_v3Vec1;
	// Y方向の傾斜
	VECTOR m_v3Vec2;

	// 経過時間
	int m_time;
	// 表示画像
	int m_handle;
};