#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <vector>

class RecoveryBase;
class ShotBase;
class Bg;
class Player;
class SceneMain;

/// <summary>
/// 敵の基底クラス
/// </summary>
class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Init(Bg* pBg, Player* pPlayer);
	virtual void Update();
	virtual void Draw();

	// 敵がダメージを受けた時の処理
	virtual void OnDamage();
	// マップチップとの当たり判定
	virtual void HitCollision(Rect chipRect);
	// 敵キャラクターをスタートさせる
	virtual void Start(float posX, float posY, float moveRangeX) = 0;

	// メンバー変数にアクセスする
	void SetMain(SceneMain* pMain) { m_pMain = pMain; }

	// 存在しているかの判定		true:存在している
	bool IsExist() const { return m_isExist; }
	// 敵が倒されたか取得
	bool IsDead() const { return m_isDead; }
	// HPの取得
	float GetHp() const { return m_hp; }
	// 現在座標の取得
	Vec2 GetPos() const { return m_pos; }
	// 当たり判定を取得する
	Rect GetColRect() const { return m_colRect; }

protected:
	// メインシーンのポインタ
	SceneMain* m_pMain;
	// 背景クラスのポインタ
	Bg* m_pBg;
	// プレイヤーのポインタ
	Player* m_pPlayer;
	// 回復アイテムのポインタ
	RecoveryBase* m_pRecovery;
	// ショットのポインタ
	std::vector<ShotBase*> m_pShot;

	// グラフィックのハンドル
	int m_handle;

	// 存在するかフラグ true:存在する
	bool m_isExist;	
	// 敵のHP
	float m_hp;
	// 敵が倒されたかどうか // true:倒された
	bool m_isDead;

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
	Dir m_dir;

	// スタート時の敵の座標
	Vec2 m_startPos;
	// 横の移動範囲
	float m_moveRangeX;

	// 音
	int m_damageSE;	// ダメージ時のSE

	// ダメージエフェクト
	int m_damageEffect; // ダメージ時のエフェクト
	int m_damageFrame;	// エフェクトのアニメーション
};
