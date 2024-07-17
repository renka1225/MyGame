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
	// キャラクターの種類
	enum class CharaType
	{
		kPlayer,	// プレイヤー
		kEnemyTuto,	// チュートリアルの敵
	};

	// キャラクターのステータス
	struct Status
	{
		float maxHp;			// 最大HP
		float punchPower;		// パンチの攻撃力
		float kickPower;		// キックの攻撃力
		float maxMoveSpeed;		// 最大の移動速度
	};
	Status m_status;

	CharacterBase();
	~CharacterBase() {};
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void OnDamage(float damage);	// ダメージを受けた際の処理

	VECTOR GetPos() const { return m_pos; }	// 現在地取得
	float GetHp() const { return m_hp; }	// 現在のHPを取得

protected:
	//// アニメーションステートの更新
	//void UpdateAnimState(State prevState);
	//// アニメーション処理
	//void UpdateAnim();
	//// アニメーションを再生する
	//void PlayAnim(AnimKind PlayAnimIndex);

protected:
	std::shared_ptr<LoadData> m_pLoadData;	// キャラクター情報を取得
	std::shared_ptr<UIGauge> m_pUIGauge;	// バトル中に表示するHPのゲージ

	float m_hp;			// HP
	VECTOR m_pos;		// 位置
	float m_moveSpeed;	// 移動速度
	float m_angle;		// 向いている方向の角度
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