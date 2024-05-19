#pragma once
#include "DxLib.h"

/// <summary>
/// 立方体2クラス
/// </summary>
class Cube2
{
public:
	Cube2();
	~Cube2() {};
	void Draw();

	// 立方体の中心点を取得
	VECTOR GetPos() const { return m_pos; }
	// 立方体のサイズを取得
	VECTOR GetScale() const { return m_scale; }

private:
	// 立方体2の中心点
	VECTOR m_pos;
	// 立方体2のサイズ
	VECTOR m_scale;

	// 立方体の3Dモデル
	int m_handle;
};

