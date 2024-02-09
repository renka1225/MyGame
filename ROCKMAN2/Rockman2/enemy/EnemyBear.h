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

	virtual void Init(Bg* pBg, Player* pPlayer) override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Start(float posX, float posY, float moveRangeX) override;
	virtual void HitCollision(Rect chipRect) override;
	virtual void OnDamage() override;

	// �A�j���[�V����
	void UpdateAnim();
	// �F�̕`��
	void DrawBear(int x, int y);

private:
	// �A�j���[�V�����̎��
	enum Anim
	{
		kIdle,		// �ҋ@
		kRun,		// �ːi
		kRecovery,	// ��
	};
	// ���݂̃A�j���[�V�������
	Anim m_animation;
	// �ҋ@�A�j���[�V����
	int m_idleAnimFrame;
	// �ːi�A�j���[�V����
	int m_runAnimFrame;	
	// �񕜃A�j���[�V����
	int m_recoveryAnimFrame;
};

