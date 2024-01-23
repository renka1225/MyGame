#pragma once
#include "EnemyBase.h"

/// <summary>
/// �F�̓G�N���X
/// </summary>
class EnemyBear : public EnemyBase
{
public:
	EnemyBear();
	virtual ~EnemyBear();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Start(float posX, float posY) override;
	virtual void OnDamage() override;

private:
	// �����A�j���[�V����
	int m_walkAnimFrame;
};

