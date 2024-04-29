#pragma once
#include "ModelBase.h"

/// <summary>
/// 地面の3Dモデルクラス
/// </summary>
class ModelGround : public ModelBase
{
public:
	ModelGround(int model, VECTOR pos);
	virtual ~ModelGround();
	virtual void Update() override;

private:
	static constexpr float kScale = 30.0f;	// モデルの拡大率

	static constexpr float kGroundScaleWidth = 500.0f;	// 地面横の拡大率
	static constexpr float kGroundScaleHeight = 20.0f;	// 地面高さの拡大率
	static constexpr float kGroundScaleDepth = 700.0f;	// 地面奥行きの拡大率
};