#pragma once
#include "DxLib.h"
#include <memory>

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
	std::shared_ptr<WorldSprite> m_sprite;

	VECTOR m_backgroundPos;		// wiÌ\¦Êu
	VECTOR m_treePos;			// ØÌ\¦Êu

	int m_background;	// wiÌæ
	int m_groundModel;	// nÊÌ3Df
	int m_treeModel;	// ØÌ3Df

private:	// è
	static constexpr int kWidth = 576;				// wiæÌ¡
	static constexpr int kHeight = 324;				// wiæÌc
	static constexpr float kBackScele = 300.0f;		// wiæÌgå¦
	static constexpr float kBackPosY = 60.0f;		// wiæÌ\¦ÊuY
	static constexpr float kBackPosZ = 30.0f;		// wiæÌ\¦ÊuZ
};

