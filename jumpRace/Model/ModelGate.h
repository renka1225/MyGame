#pragma once
#include "ModelBase.h"

/// <summary>
/// �Q�[�g��3D���f���N���X
/// </summary>
class ModelGate : public ModelBase
{
public:
	ModelGate(int model, VECTOR pos);
	virtual ~ModelGate();
	virtual void Update() override;

private:
	static constexpr float kScale = 20.0f;	// ���f���̊g�嗦
};

