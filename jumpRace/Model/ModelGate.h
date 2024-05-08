#pragma once
#include "ModelBase.h"

/// <summary>
/// ゲートの3Dモデルクラス
/// </summary>
class ModelGate : public ModelBase
{
public:
	ModelGate(int model, VECTOR pos);
	virtual ~ModelGate();
	virtual void Update() override;

private:
	static constexpr float kScale = 20.0f;	// モデルの拡大率
};

