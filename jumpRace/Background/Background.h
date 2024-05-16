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

private:	// ’è”
	static constexpr int kBgNum = 4;				// ”wŒi‰æ‘œ‚Ì”
	static constexpr int kWidth = 576;				// ”wŒi‰æ‘œ‚Ì‰¡•
	static constexpr int kHeight = 324;				// ”wŒi‰æ‘œ‚Ìc•

	static constexpr float kBgPosY = 100.0f;		// ”wŒi‰æ‘œ‚Ì•\¦ˆÊ’uY
	static constexpr float kBgPosZ = 30.0f;			// ”wŒi‰æ‘œ‚Ì•\¦ˆÊ’uZ
	static constexpr float kBg2PosY = 90.0f;		// ”wŒi‰æ‘œ2‚Ì•\¦ˆÊ’uY
	static constexpr float kBg2PosZ = 20.0f;		// ”wŒi‰æ‘œ2‚Ì•\¦ˆÊ’uZ
	static constexpr float kBg3PosY = 100.0f;		// ”wŒi‰æ‘œ3‚Ì•\¦ˆÊ’uY
	static constexpr float kBg3PosZ = 18.0f;		// ”wŒi‰æ‘œ3‚Ì•\¦ˆÊ’uZ
	static constexpr float kBg4PosY = 190.0f;		// ”wŒi‰æ‘œ4‚Ì•\¦ˆÊ’uY
	static constexpr float kBg4PosZ = 17.0f;		// ”wŒi‰æ‘œ4‚Ì•\¦ˆÊ’uZ
	static constexpr float kBgScale = 250.0f;		// ”wŒi‰æ‘œ‚ÌŠg‘å—¦
	static constexpr float kBg2Scale = 200.0f;		// ”wŒi‰æ‘œ2‚ÌŠg‘å—¦
	static constexpr float kBg3Scale = 250.0f;		// ”wŒi‰æ‘œ3‚ÌŠg‘å—¦
	static constexpr float kBg4Scale = 250.0f;		// ”wŒi‰æ‘œ4‚ÌŠg‘å—¦
	static constexpr float kBgMove = 3.0f;			// ”wŒi‚ÌˆÚ“®—Ê
};
