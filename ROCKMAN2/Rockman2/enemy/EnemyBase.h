#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <vector>

class RecoveryBase;
class ShotBase;
class Bg;
class SceneMain;

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

	// 敵がダメージを受けた時の処理
	virtual void OnDamage();
	// 敵キャラクターをスタートさせる
	virtual void Start() = 0;

	// メンバー変数にアクセスする
	void SetMain(SceneMain* pMain) { m_pMain = pMain; }
	void SetBg(Bg* pBg) { m_pBg = pBg; }

	// 存在しているかの判定		true:存在している
	bool IsExist() const { return m_isExist; }
	// HPの取得
	int GetHp() const { return m_hp; }
	// 現在座標の取得
	Vec2 GetPos() const { return m_pos; }
	// 当たり判定を取得する
	Rect GetColRect() const { return m_colRect; }

protected:
	// メインシーンのポインタ
	SceneMain* m_pMain;
	// 背景クラスのポインタ
	Bg* m_pBg;
	// 回復アイテムのポインタ
	RecoveryBase* m_pRecovery;
	// ショットのポインタ
	std::vector<ShotBase*> m_pShot;

	// グラフィックのハンドル
	int m_handle;
	// 存在するかフラグ true:存在する
	bool m_isExist;	
	// 敵のHP
	int m_hp;

	// 表示位置
	Vec2 m_pos;
	// 当たり判定の矩形
	Rect m_colRect;
	// 移動量
	Vec2 m_vec;

	// 向いている方向
	enum Dir
	{
		kDirLeft,	// 左
		kDirRight,	// 右
	};

	// 向いている方向
	Dir m_dir;
};
