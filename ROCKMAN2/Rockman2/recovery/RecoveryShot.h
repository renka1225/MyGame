#pragma once
#include "RecoveryBase.h"

/// <summary>
/// 弾数回復クラス
/// </summary>
class RecoveryShot:public RecoveryBase
{
public:
	RecoveryShot();
	virtual ~RecoveryShot();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	// 弾が存在しているか
	bool IsExist() const { return m_isExist; }
	// 当たり判定の矩形を取得する
	Rect GetColRect() const { return m_colRect; }

private:
	// グラフィックのハンドル
	int m_shotSmallRecHandle;	// 弾小回復
	int m_shotGreatRecHandle;	// 弾大回復

	// 弾数回復
	float m_shotSmallRecovery; // 小回復
	float m_shotGreatRecovery; // 大回復

	// 画面内に存在するか
	bool m_isExist;
	// 表示位置
	Vec2 m_pos;
	// 当たり判定の矩形
	Rect m_colRect;
};

