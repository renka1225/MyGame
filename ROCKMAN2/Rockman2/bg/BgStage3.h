#pragma once
#include "Bg.h"

/// <summary>
/// �X�e�[�W3�̔w�i�N���X
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

