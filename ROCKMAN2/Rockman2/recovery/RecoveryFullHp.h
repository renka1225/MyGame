#pragma once
#include "RecoveryBase.h"

class Player;

/// <summary>
/// HP全回復クラス
/// </summary>
class RecoveryFullHp : public RecoveryBase
{
public:
	RecoveryFullHp();
	virtual ~RecoveryFullHp();

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
	// プレイヤーのポインタ
	Player* m_pPlayer;

	// グラフィックのハンドル
	int m_hpFullRecHandle;
	// 画面内に存在するか
	bool m_isExist;
	// 表示位置
	Vec2 m_pos;
	// 当たり判定の矩形
	Rect m_colRect;
};

