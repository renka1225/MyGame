#pragma once
#include "EnemyBase.h"
#include "Vec2.h"

/// <summary>
/// �܂����Ԃ낤�̃N���X
/// </summary>
class Matasaburo : public EnemyBase
{
public:
	Matasaburo();
	virtual ~Matasaburo();

	virtual void Update() override;
	virtual void Start() override;

private:
	int m_handle;
};

