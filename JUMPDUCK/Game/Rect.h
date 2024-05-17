#pragma once
#include "DxLib.h"

/// <summary>
/// 矩形の座標を管理するクラス
/// </summary>
class Rect
{
public:
	Rect();
	virtual ~Rect();
	// 四角の描画
	void Draw(unsigned int color, bool isFill);
	// 中心座標と幅高さを指定
	void SetCenter(float x, float y, float z, float width, float height);

	// 情報取得
	float GetWidth() const;			// 矩形の幅
	float GetHeight() const;		// 矩形の高さ
	VECTOR GetCenter() const;		// 矩形の中心座標

	// 矩形同士の当たり判定
	bool IsCollision(const Rect& rect);

public:
	float m_left;	// 左上のX座標
	float m_top;	// 左上のY座標
	float m_right;	// 右下のX座標
	float m_bottom;	// 右下のY座標
};