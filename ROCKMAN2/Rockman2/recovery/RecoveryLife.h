#pragma once
#include "RecoveryBase.h"

/// <summary>
/// 残機回復クラス
/// </summary>
class RecoveryLife :public RecoveryBase
{
public:
	RecoveryLife();
	virtual ~RecoveryLife();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	// 弾が存在しているか
	bool IsExist() const { return m_isExist; }
	// 当たり判定の矩形を取得する
	Rect GetColRect() const { return m_colRect; }

private:
	// グラフィックのハンドル
	int m_lifeRecHandle;

	// 残機回復
	int m_lifeRecovery;

	// 画面内に存在するか
	bool m_isExist;
	// 表示位置
	Vec2 m_pos;
	// 当たり判定の矩形
	Rect m_colRect;

};

