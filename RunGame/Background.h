#pragma once
#include "DxLib.h"
#include <memory>

class ManagerModel;
/// <summary>
/// ”wŒiƒNƒ‰ƒX
/// </summary>
class Background
{
public:
	Background(std::shared_ptr<ManagerModel> pModel);
	~Background() {};

	void Init();
	void Update();
	void Draw();
	void End();

private:
	// ƒ‚ƒfƒ‹ƒNƒ‰ƒX‚Ìƒ|ƒCƒ“ƒ^
	std::shared_ptr<ManagerModel> m_pModel;

	// •\¦ˆÊ’u
	VECTOR m_pos;

	// ”g‚Ì•\¦ˆÊ’u
	int m_wavePosX;

	// ”wŒi
	int m_background;

private:	// ’è”
	static constexpr float kBackgroundSize = 300.0f;	// ”wŒi‰æ‘œ‚ÌƒTƒCƒY

	static constexpr int kWaveAmplitude = 10;	// ”g‚ÌU•
	static constexpr int kWaveFrequency = 100;	// ”g‚Ìü”g”
	static constexpr int kWaveRange = 1000;		// ”g‚Ì•`‰æ”ÍˆÍ
	static constexpr int kDrawWaveY = 450;		// ”g‚Ì•`‰æˆÊ’uYÀ•W
};

