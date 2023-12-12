#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class EnemyBase;
class Player;

/// <summary>
/// 回復アイテム基底クラス
/// </summary>
class RecoveryBase
{
public:
	RecoveryBase();
	virtual ~RecoveryBase();

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	// アイテムをドロップする
	virtual void Start(Vec2 pos) = 0;

	// メンバ変数にアクセスする
	void SetMain(SceneMain* pMain) { m_pMain = pMain; }
	void SetEnemy(EnemyBase* pEnemy) { m_pEnemy = pEnemy; }

	// アイテムが存在しているか
	bool IsExist() const { return m_isExist; }
	// 回復アイテムの当たり判定を取得する
	Rect GetColRect() const { return m_colRect; }
	// 現在座標の取得
	Vec2 GetPos() const { return m_pos; }

private:
	// SceneMainの関数を呼び出すためにポインタを覚えておく
	SceneMain* m_pMain;
	// アイテムをドロップする敵のポインタを覚えておく
	EnemyBase* m_pEnemy;

	// 画面内に存在しているか
	bool m_isExist;

	// 表示位置
	Vec2 m_pos;
	// 当たり判定用の矩形
	Rect m_colRect;
};

