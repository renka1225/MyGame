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
	static constexpr int kWidth = 2304;					// wiæÌ¡
	static constexpr int kHeight = 1296;				// wiæÌc
	static constexpr float kBackScele = 100.0f;			// wiæÌgå¦
	static constexpr float kGroundPosY = 100.0f;		// nÊÌÊuY
	static constexpr float kGroundPosZ = 0.0f;			// nÊÌÊuZ
	static constexpr float kGroundScaleWidth = 300.0f;	// nÊ¡Ìgå¦
	static constexpr float kGroundScaleHeight = 20.0f;	// nÊ³Ìgå¦
	static constexpr float kGroundScaleDepth = 700.0f;	// nÊs«Ìgå¦
};

