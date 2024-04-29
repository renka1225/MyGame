#pragma once
#include "DxLib.h"
#include <memory>

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
	std::shared_ptr<WorldSprite> m_sprite;

	VECTOR m_backgroundPos;		// ”wŒi‚Ì•\¦ˆÊ’u
	VECTOR m_treePos;			// –Ø‚Ì•\¦ˆÊ’u

	int m_background;	// ”wŒi‚Ì‰æ‘œ
	int m_groundModel;	// ’n–Ê‚Ì3Dƒ‚ƒfƒ‹
	int m_treeModel;	// –Ø‚Ì3Dƒ‚ƒfƒ‹

private:	// ’è”
	static constexpr int kWidth = 2304;					// ”wŒi‰æ‘œ‚Ì‰¡•
	static constexpr int kHeight = 1296;				// ”wŒi‰æ‘œ‚Ìc•
	static constexpr float kBackScele = 100.0f;			// ”wŒi‰æ‘œ‚ÌŠg‘å—¦
};

