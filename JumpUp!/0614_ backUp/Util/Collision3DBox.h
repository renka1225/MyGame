#pragma once

/// <summary>
/// 3Dの四角の当たり判定処理を行う
/// </summary>
class Collision3DBox
{
public:
	Collision3DBox();
	~Collision3DBox() {};

	// 直方体の描画
	void Draw(unsigned int color, VECTOR pos, VECTOR size);
	// 中心座標と幅高さ奥行を指定
	void SetCenter(VECTOR pos, VECTOR size);
	// バウンドボックスを作成
	void CreateBoundingBox(int handle);
	// 直方体同士の当たり判定
	bool IsCollision(const Collision3DBox& col3DBox);

	// 中心点取得
	VECTOR GetCenter() const { return m_centerPos; }	// 矩形の中心座標

public:
	VECTOR m_minPos;	// ローカル座標での最小値
	VECTOR m_maxPos;	// ローカル座標での最大値
	VECTOR m_centerPos;	// モデルの中心点

	float m_left;	// 左下手前のX座標
	float m_bottom;	// 左下手前のY座標
	float m_front;	// 左下手前のZ座標
	float m_right;	// 右上奥のX座標
	float m_top;	// 右上奥のY座標
	float m_back;	// 右上奥のZ座標
};

