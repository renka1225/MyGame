#pragma once
#include "ModelBase.h"

/// <summary>
/// �؂�3D���f���N���X
/// </summary>
class ModelTree : public ModelBase
{
public:
	ModelTree(int model, VECTOR pos);
	virtual ~ModelTree();
	virtual void Update() override;
};

