#pragma once
#include "Vec2.h"
#include <vector>
#include <list>

/// <summary>
/// 花火クラス
/// </summary>
class Fireworks
{
public:
	Fireworks(int startX);
	void Update();
	void Draw();
	void Fire();

private:
	/// <summary>
	/// 打ちあがり
	/// </summary>
	void RiseUpdate();
	void RiseDraw();

	/// <summary>
	/// 爆発
	/// </summary>
	void ExplodeUpdate();
	void ExplodeDraw();

	/// <summary>
	/// 待機
	/// </summary>
	void WaitUpdate();
	void WaitDraw();

	/*using UpdateFunc_t = void (Fireworks::*)();
	using DrawFunc_t = void (Fireworks::*)();
	UpdateFunc_t updateFunc_;
	UpdateFunc_t drawFunc_;*/

	// 花火の中心
	Vec2 m_pos;
	std::list<Vec2> m_historyPos;

	// 飛び散った時の花火のパーツ
	struct FirePart
	{
		Vec2 m_pos;	// 現在の座標
		Vec2 m_vec;	// 速度(重力の影響を受ける)
		std::list<Vec2> m_historyPos;
	};
	std::vector<FirePart> m_fireParts;	// 四方八方に散らす
	int m_height;
	int m_frame;
};

