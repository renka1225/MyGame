#pragma once
#include "Bg.h"

/// <summary>
/// ステージ3の背景クラス
/// </summary>
class BgStage3 : public Bg
{
public:
	BgStage3();
	virtual ~BgStage3();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
};

