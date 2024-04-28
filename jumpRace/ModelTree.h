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
};

