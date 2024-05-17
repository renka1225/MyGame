#pragma once
#include "DxLib.h"

/// <summary>
/// 3Dモデルの基底クラス
/// </summary>
class ModelBase
{
public:
	ModelBase(int model);
	virtual ~ModelBase() {};
	virtual void Update() = 0;
	virtual void Draw();

protected:
	VECTOR m_pos;	// 3Dモデルの表示位置
	int m_model;	// 3Dモデル
};