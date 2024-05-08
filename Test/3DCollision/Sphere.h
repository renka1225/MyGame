#pragma once
#include "DxLib.h"

/// <summary>
/// ‹…
/// </summary>
class Sphere
{
public:
	Sphere();
	~Sphere();
	void Init();
	void Update();
	void Draw();

private:
	VECTOR m_pos;		// ˆÚ“®‚·‚é‹…‚ÌˆÊ’u
	VECTOR m_targetPos;	// “®‚©‚È‚¢‹…‚ÌˆÊ’u
	bool m_isHit;		// “–‚½‚Á‚Ä‚¢‚é‚©

	static constexpr float kRadius = 40.0f;	// ”¼Œa
	static constexpr int kDivNum = 32;
};

