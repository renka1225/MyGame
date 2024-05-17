#pragma once
#include "ModelBase.h"

/// <summary>
/// �n�ʂ�3D���f���N���X
/// </summary>
class ModelGround : public ModelBase
{
public:
	ModelGround(int model, VECTOR pos);
	virtual ~ModelGround();
	virtual void Update() override;

private:
	static constexpr float kScale = 30.0f;	// ���f���̊g�嗦

	static constexpr float kGroundScaleWidth = 500.0f;	// �n�ʉ��̊g�嗦
	static constexpr float kGroundScaleHeight = 20.0f;	// �n�ʍ����̊g�嗦
	static constexpr float kGroundScaleDepth = 700.0f;	// �n�ʉ��s���̊g�嗦
};