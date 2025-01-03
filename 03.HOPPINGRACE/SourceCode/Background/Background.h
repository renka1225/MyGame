#pragma once
#include "DxLib.h"
#include <memory>
#include <vector>

class ManagerModel;
class WorldSprite;

/// <summary>
/// wiNX
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
	std::vector<int> m_bgHandle;	// wiÌæ

private:	// è
	static constexpr int kBgNum = 4;				// wiæÌ
	static constexpr int kWidth = 576;				// wiæÌ¡
	static constexpr int kHeight = 324;				// wiæÌc

	static constexpr float kBgPosY = 100.0f;		// wiæÌ\¦ÊuY
	static constexpr float kBgPosZ = 30.0f;			// wiæÌ\¦ÊuZ
	static constexpr float kBg2PosY = 90.0f;		// wiæ2Ì\¦ÊuY
	static constexpr float kBg2PosZ = 20.0f;		// wiæ2Ì\¦ÊuZ
	static constexpr float kBg3PosY = 100.0f;		// wiæ3Ì\¦ÊuY
	static constexpr float kBg3PosZ = 18.0f;		// wiæ3Ì\¦ÊuZ
	static constexpr float kBg4PosY = 190.0f;		// wiæ4Ì\¦ÊuY
	static constexpr float kBg4PosZ = 17.0f;		// wiæ4Ì\¦ÊuZ
	static constexpr float kBgScale = 250.0f;		// wiæÌgå¦
	static constexpr float kBg2Scale = 200.0f;		// wiæ2Ìgå¦
	static constexpr float kBg3Scale = 250.0f;		// wiæ3Ìgå¦
	static constexpr float kBg4Scale = 250.0f;		// wiæ4Ìgå¦
	static constexpr float kBgMove = 3.0f;			// wiÌÚ®Ê
};
