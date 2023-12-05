#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <vector>

class ShotBase;

/// <summary>
/// 敵の基底クラス
/// </summary>
class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Update() = 0;
	virtual void Draw() = 0;

	// メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }
	// 存在しているかの判定		true:存在している
	bool IsExist() const { return m_isExist; }
	// HPの取得
	int GetHp() const { return m_hp; }
	// 現在座標の取得
	Vec2 GetPos() const { return m_pos; }
	// 当たり判定を取得する
	Rect GetColRect() const { return m_colRect; }

	// 敵キャラクターをスタートさせる
	virtual void Start() = 0;

	// 敵がダメージを受けた時の処理
	virtual void OnDamage(int damage) = 0;

protected:
	// 当たり判定を設定する
	virtual void UpdateCollision();

protected:
	// ショット
	std::vector<ShotBase*> m_pShot;

	int m_handle;	// グラフィックのハンドル
	bool m_isExist;	// 存在するかフラグ true:存在する
	int m_hp;		// 敵のHP

	// 表示位置
	Vec2 m_pos;
	// 当たり判定の矩形
	Rect m_colRect;
	// 移動量
	Vec2 m_vec;
};

