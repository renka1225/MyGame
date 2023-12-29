#pragma once
#include "RecoveryBase.h"

/// <summary>
/// HP小回復クラス
/// </summary>
class RecoverySmallHp : public RecoveryBase
{
public:
	RecoverySmallHp();
	virtual ~RecoverySmallHp();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	// アイテムをドロップする
	virtual void Start(Vec2 pos) override;

	// 弾が存在しているか
	bool IsExist() const { return m_isExist; }
	// 当たり判定の矩形を取得する
	Rect GetColRect() const { return m_colRect; }
	// 現在座標の取得
	Vec2 GetPos() const { return m_pos; }

private:
	// グラフィックのハンドル
	int m_handle;
	// 表示時間
	int m_frame;
};

