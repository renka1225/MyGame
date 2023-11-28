#pragma once
#include "ShotBase.h"

class ShotMetal : public ShotBase
{
public:
	ShotMetal();
	virtual ~ShotMetal();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	// 弾をスタートさせる
	virtual void Start(Vec2 pos) override;

	// メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }

private:
	// グラフィックのハンドル
	int m_handle;

	// 現在の弾エネルギー数
	float m_energy;
};

