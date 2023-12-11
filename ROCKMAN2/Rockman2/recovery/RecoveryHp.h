#pragma once
#include "RecoveryBase.h"


/// <summary>
/// HP回復クラス
/// </summary>
class RecoveryHp : public RecoveryBase
{
public:
	RecoveryHp();
	virtual ~RecoveryHp();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Start() override;

	// 弾が存在しているか
	bool IsExist() const { return m_isExist; }
	// 当たり判定の矩形を取得する
	Rect GetColRect() const { return m_colRect; }

private:
	// グラフィックのハンドル
	int m_hpSmallRecHandle;		// HP小回復
	int m_hpGreatRecHandle;		// HP大回復
	int m_hpFullRecHandle;		// HP全回復

	// 画面内に存在するか
	bool m_isExist;
	// 表示位置
	Vec2 m_pos;
	// 当たり判定の矩形
	Rect m_colRect;
};

