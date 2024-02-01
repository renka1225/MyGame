#pragma once
#include "ShotBase.h"
#include <vector>

class ShotFire : public ShotBase
{
public:
	ShotFire();
	virtual ~ShotFire();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	// 弾をスタートさせる
	virtual void Start(Vec2 pos) override;

private:
	// グラフィックのハンドル
	int m_handle;		// 弾
};

