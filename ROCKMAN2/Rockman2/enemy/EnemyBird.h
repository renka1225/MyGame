#pragma once
#include "EnemyBase.h"

/// <summary>
/// ���̓G�N���X
/// </summary>
class EnemyBird : public EnemyBase
{
public:
	EnemyBird();
	virtual ~EnemyBird();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Start(float posX, float posY) override;
	virtual void OnDamage() override;

private:
	// �����A�j���[�V����
	int m_flyAnimFrame;
};

