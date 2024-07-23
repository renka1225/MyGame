#pragma once
#include <memory>

class LoadData;
class UIGauge;

/// <summary>
/// キャラクターの基底クラス
/// </summary>
class CharacterBase
{
public:
	CharacterBase();
	~CharacterBase() {};
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void OnDamage(float damage);		// ダメージを受けた際の処理

	VECTOR GetPos() const { return m_pos; }			// 現在地取得
	float GetHp() const { return m_hp; }			// 現在のHPを取得
	bool GetIsGuard() const { return m_isGuard; }	// ガード中かどうか取得

	// キャラクターの種類
	enum class CharaType
	{
		kPlayer,	// プレイヤー
		kEnemyTuto,	// チュートリアルの敵
	};

	// アニメーション種別
	enum class AnimKind
	{
		kNone = -1,		// なし
		kAvoid = 0,		// 回避
		kDown = 1,		// 倒れる
		kFightIdle = 2, // 構え(停止中)
		kFightWalk = 3, // 構え(移動中)
		kGettingUp = 4, // 起き上がる
		kGrab = 5,		// 掴み
		kGuard = 6,		// ガード
		kKick = 7,		// キック
		kPunch = 8,		// パンチ
		kComboPunch = 9,// コンボパンチ
		kReceive = 10,	// 攻撃を受ける
		kRun = 11,		// 移動
		kStand = 12,	// 待機
		kStumble = 13,	// 掴み失敗
	};

	// アニメーション速度
	struct AnimSpeed
	{
		float none;			// なし
		float avoid;		// 回避
		float down;			// 倒れる
		float fightIdle;	// 構え(停止中)
		float fightWalk;	// 構え(移動中)
		float gettingUp;	// 起き上がる
		float grab;			// 掴み
		float guard;		// ガード
		float kick;			// キック
		float punch;		// パンチ
		float comboPunch;	// コンボパンチ
		float receive;		// 攻撃を受ける
		float run;			// 移動
		float stand;		// 待機
		float Stumble;		// 掴み失敗
	};
	AnimSpeed m_animSpeed;

	// キャラクターのステータス
	struct Status
	{
		float maxHp;			// 最大HP
		float punchPower;		// パンチの攻撃力
		float kickPower;		// キックの攻撃力
		float maxMoveSpeed;		// 最大の移動速度
		float fightWalkSpeed;	// 構え時の移動速度
		float acceleration;		// 加速度
		float deceleration;		// 減速度
		float avoidDist;		// 回避の距離
	};
	Status m_status;

	// 当たり判定情報
	struct CollisionInfo
	{
		float bodyHeight;		// 全身の当たり判定の高さ
		float bodyRadius;		// 全身の当たり判定の半径
		float aimRadius;		// 腕の当たり判定の半径
		float legRadius;		// 脚の当たり判定の半径
		VECTOR armStartPos;		// 腕の当たり判定始点
		VECTOR armEndPos;		// 腕の当たり判定終点
		VECTOR legStartPos;		// 脚の当たり判定始点
		VECTOR legEndPos;		// 脚の当たり判定終点
		VECTOR bodyTopPos;		// 全身の当たり判定始点
		VECTOR bodyBottomPos;	// 全身の当たり判定終点
	};
	CollisionInfo m_colInfo;

protected:
	// 当たり判定位置の更新
	void UpdateCol();
	// アニメーションを再生する
	void PlayAnim(AnimKind playAnimIndex);
	// アニメーション処理
	virtual void UpdateAnim() = 0;
	
protected:
	std::shared_ptr<LoadData> m_pLoadData;	// キャラクター情報を取得
	std::shared_ptr<UIGauge> m_pUIGauge;	// バトル中に表示するHPのゲージ

	float m_hp;			// HP
	VECTOR m_pos;		// 位置
	float m_moveSpeed;	// 移動速度
	float m_angle;		// 向いている方向の角度
	bool m_isAttack;	// 攻撃中かどうか(true:攻撃中)
	bool m_isGuard;		// ガード中かどうか(ture:ガード中)
	int m_modelHandle;	// キャラクターの3Dモデル

	// アニメーション情報
	int m_currentPlayAnim;		// 再生中のアニメーションのアタッチ番号
	float m_currentAnimCount;	// 再生中のアニメーションの再生時間
	int m_prevPlayAnim;			// 前の再生アニメーションのアタッチ番号
	float m_prevAnimCount;		// 前の再生アニメーションの再生時間
	float m_animBlendRate;		// 現在と過去のアニメーションのブレンド率

	struct Collision
	{
		VECTOR armStartPos;		// 腕の当たり判定始点
		VECTOR armEndPos;		// 腕の当たり判定終点
		VECTOR legStartPos;		// 脚の当たり判定始点
		VECTOR legEndPos;		// 脚の当たり判定終点
		VECTOR bodyTopPos;		// 全身の当たり判定始点
		VECTOR bodyBottomPos;	// 全身の当たり判定終点
	};
	Collision m_col;
};