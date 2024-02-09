#pragma once
#include "EnemyBase.h"

/// <summary>
/// 熊の敵クラス
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

	// アニメーション
	void UpdateAnim();
	// 熊の描画
	void DrawBear(int x, int y);

private:
	// アニメーションの種類
	enum Anim
	{
		kIdle,		// 待機
		kRun,		// 突進
		kRecovery,	// 回復
	};
	// 現在のアニメーション状態
	Anim m_animation;
	// 待機アニメーション
	int m_idleAnimFrame;
	// 突進アニメーション
	int m_runAnimFrame;	
	// 回復アニメーション
	int m_recoveryAnimFrame;
};

