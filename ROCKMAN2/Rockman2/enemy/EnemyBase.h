#pragma once
#include "Vec2.h"
#include "Rect.h"

/// <summary>
/// 敵の基底クラス
/// </summary>
class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	// メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }
	// 存在しているかの判定		true:存在している
	bool IsExist() const { return m_isExist; }
	// 現在座標の取得
	Vec2 GetPos() const { return m_pos; }
	// 当たり判定を取得する
	Rect GetColRect() const { return m_colRect; }

	// 敵キャラクターをスタートさせる
	virtual void Start() = 0;

protected:
	// m_posを左上に、m_handleのグラフィックサイズを幅高さにした当たり判定を設定する
	virtual void UpdateCollision();

protected:
	int m_handle;	// グラフィックのハンドル

	bool m_isExist;	// 存在するかフラグ(使用中かどうか)

	// 表示位置
	Vec2 m_pos;
	// 当たり判定の矩形
	Rect m_colRect;
	// 移動量
	Vec2 m_vec;
};

