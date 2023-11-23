#pragma once
#include "ShotBase.h"
#include <vector>

class ShotBuster : public ShotBase
{
public:
	ShotBuster();
	virtual ~ShotBuster();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	// メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }

	// 弾をスタートさせる
	virtual void Start(Vec2 pos) override;

private:
	// グラフィックのハンドル
	int m_handle;
};

