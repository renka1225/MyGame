#pragma once
#include <memory>

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

protected:
	std::shared_ptr<UIGauge> m_pUIGauge;	// バトル中に表示するHPのゲージ

	float m_hp;			// HP
	VECTOR m_pos;		// 位置
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