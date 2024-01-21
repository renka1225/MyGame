#pragma once
#include "Bg.h"

/// <summary>
/// ステージ2の背景クラス
/// </summary>
class BgStage2 : public Bg
{
public:
	BgStage2();
	virtual ~BgStage2();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
};

