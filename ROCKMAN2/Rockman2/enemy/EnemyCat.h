#pragma once
#include "EnemyBase.h"

/// <summary>
/// �L�̓G�N���X
/// </summary>
class EnemyCat : public EnemyBase
{
public:
	EnemyCat();
	virtual ~EnemyCat();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Start(float posX, float posY) override;
	virtual void OnDamage() override;

private:
	// �����A�j���[�V����
	int m_walkAnimFrame;
};

