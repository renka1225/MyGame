#pragma once
#include "RecoveryBase.h"

/// <summary>
/// 弾数回復クラス
/// </summary>
class RecoverySmallShot:public RecoveryBase
{
public:
	RecoverySmallShot();
	virtual ~RecoverySmallShot();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	// アイテムをドロップする
	virtual void Start(Vec2 pos) override;

	// 弾が存在しているか
	bool IsExist() const { return m_isExist; }
	// 当たり判定の矩形を取得する
	Rect GetColRect() const { return m_colRect; }

private:
	// アイテムをドロップする敵のポインタ
	EnemyBase* m_pEnemy;

	// グラフィックのハンドル
	int m_shotSmallRecHandle;	// 弾小回復

	// 画面内に存在するか
	bool m_isExist;
	// 表示位置
	Vec2 m_pos;
	// 当たり判定の矩形
	Rect m_colRect;
};

