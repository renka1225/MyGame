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

	virtual void Init(Bg* pBg, Player* pPlayer) override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Start(float posX, float posY, float moveRangeX) override;
	virtual void HitCollision(Rect chipRect) override;
	virtual void OnDamage() override;

private:
	// �����A�j���[�V����
	int m_walkAnimFrame;
};

