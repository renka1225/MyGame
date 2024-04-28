#pragma once
#include "ModelBase.h"

/// <summary>
/// –Ø‚Ì3Dƒ‚ƒfƒ‹ƒNƒ‰ƒX
/// </summary>
class ModelTree : public ModelBase
{
public:
	ModelTree(int model, VECTOR pos);
	virtual ~ModelTree();
	virtual void Update() override;
};

