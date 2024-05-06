#pragma once
#include "DxLib.h"
#include <memory>
#include <vector>

class ManagerModel;
class WorldSprite;

/// <summary>
/// ”wŒiƒNƒ‰ƒX
/// </summary>
class Background
{
public:
	Background(std::shared_ptr<ManagerModel> pModel);
	~Background();

	void Init();
	void Update();
	void Draw();

private:
	std::shared_ptr<ManagerModel> m_pModel;
	std::vector<std::shared_ptr<WorldSprite>> m_sprite;
	std::vector<int> m_bgHandle;	// ”wŒi‚Ì‰æ‘œ

	VECTOR m_bgPos;		// ”wŒi‚Ì•\¦ˆÊ’u
	VECTOR m_bg2Pos;	// ”wŒi2‚Ì•\¦ˆÊ’u
	float m_bgMove;		// ”wŒi‚ÌˆÚ“®—Ê

	// ‰æ‘œƒTƒCƒY
	struct Size
	{
		int width;
		int height;
	};

private:	// ’è”
	static constexpr int kBgNum = 4;				// ”wŒi‰æ‘œ‚Ì”
	static constexpr int kWidth = 576;				// ”wŒi‰æ‘œ‚Ì‰¡•
	static constexpr int kHeight = 324;				// ”wŒi‰æ‘œ‚Ìc•
	static constexpr float kBgPosY = 100.0f;		// ”wŒi‰æ‘œ‚Ì•\¦ˆÊ’uY
	static constexpr float kBgPosZ = 30.0f;			// ”wŒi‰æ‘œ‚Ì•\¦ˆÊ’uZ
	static constexpr float kBg2PosY = 90.0f;		// ”wŒi‰æ‘œ2‚Ì•\¦ˆÊ’uY
	static constexpr float kBg2PosZ = 20.0f;		// ”wŒi‰æ‘œ2‚Ì•\¦ˆÊ’uZ
	static constexpr float kBgScale = 250.0f;		// ”wŒi‰æ‘œ‚ÌŠg‘å—¦
	static constexpr float kBg2Scale = 200.0f;		// ”wŒi‰æ‘œ2‚ÌŠg‘å—¦
	static constexpr float kBgMove = 3.0f;			// ”wŒi‚ÌˆÚ“®—Ê
};
