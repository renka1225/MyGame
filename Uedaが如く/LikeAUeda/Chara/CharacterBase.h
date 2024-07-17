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
	virtual void OnDamage(float damage);	// ダメージを受けた際の処理

	VECTOR GetPos() const { return m_pos; }	// 現在地取得
	float GetHp() const { return m_hp; }	// 現在のHPを取得

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
		kFightIdle = 2, // 構え
		kGettingUp = 3, // 起き上がる
		kGrab = 4,		// 掴み
		kGuard = 5,		// ガード
		kKick = 6,		// キック
		kPunch = 7,		// パンチ
		kComboPunch = 8,// コンボパンチ
		kReceive = 9,	// 攻撃を受ける
		kRun = 10,		// 移動
		kStand = 11,	// 待機
		kStumble = 12,	// 掴み失敗
	};

	// アニメーション速度
	struct AnimSpeed
	{
		float none;			// なし
		float avoid;		// 回避
		float down;			// 倒れる
		float fightIdle;	// 構え
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
	};
	Status m_status;

protected:
	// アニメーション処理
	virtual void UpdateAnim() = 0;
	// アニメーションを再生する
	void PlayAnim(AnimKind playAnimIndex);

protected:
	std::shared_ptr<LoadData> m_pLoadData;	// キャラクター情報を取得
	std::shared_ptr<UIGauge> m_pUIGauge;	// バトル中に表示するHPのゲージ

	float m_hp;			// HP
	VECTOR m_pos;		// 位置
	float m_moveSpeed;	// 移動速度
	float m_angle;		// 向いている方向の角度
	bool m_isAttack;	// 攻撃中かどうか(true:攻撃中)
	int m_modelHandle;	// キャラクターの3Dモデル

	// アニメーション情報
	int m_currentPlayAnim;		// 再生中のアニメーションのアタッチ番号
	float m_currentAnimCount;	// 再生中のアニメーションの再生時間
	int m_prevPlayAnim;			// 前の再生アニメーションのアタッチ番号
	float m_prevAnimCount;		// 前の再生アニメーションの再生時間
	float m_animBlendRate;		// 現在と過去のアニメーションのブレンド率

	// 当たり判定情報
	struct CollisionInfo
	{
		// 全身の当たり判定
		VECTOR hitTopPos;
		VECTOR hitBottomPos;
		// 腕部分の当たり判定
		VECTOR armStartPos;
		VECTOR armEndPos;
		// 脚部分の当たり判定
		VECTOR legStartPos;
		VECTOR legEndPos;
	};
	CollisionInfo m_col;
};