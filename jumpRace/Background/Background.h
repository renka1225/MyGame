#pragma once
#include "DxLib.h"
#include <memory>

class WorldSprite;

/// <summary>
/// ”wŒiƒNƒ‰ƒX
/// </summary>
class Background
{
public:
	Background();
	~Background();

	void Init();
	void Update();
	void Draw();

private:
	std::shared_ptr<WorldSprite> m_sprite;

	int m_background;	// ”wŒi‚Ì‰æ‘œ
	VECTOR m_pos;		// ”wŒi‚Ì•\¦ˆÊ’u

private:	// ’è”
	static constexpr int kWidth = 2304;		// ‰æ‘œ‚Ì‰¡•
	static constexpr int kHeight = 1296;	// ‰æ‘œ‚Ìc•
	static constexpr float kScele = 100.0f;	// ‰æ‘œ‚ÌŠg‘å—¦
};

