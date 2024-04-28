#pragma once
#include "DxLib.h"

/// <summary>
/// 3D���f���̊��N���X
/// </summary>
class ModelBase
{
public:
	ModelBase(int model);
	virtual ~ModelBase() {};

	virtual void Update() = 0;
	virtual void Draw();

protected:
	VECTOR m_pos;	// 3D���f���̕\���ʒu
	int m_model;		// 3D���f��
};

