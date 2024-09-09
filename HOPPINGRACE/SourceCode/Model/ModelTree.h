#pragma once
#include "ModelBase.h"

/// <summary>
/// 木の3Dモデルクラス
/// </summary>
class ModelTree : public ModelBase
{
public:
	ModelTree(int model, VECTOR pos);
	virtual ~ModelTree();
	virtual void Update() override;

private:
	static constexpr float kScale = 30.0f;	// モデルの拡大率
};

