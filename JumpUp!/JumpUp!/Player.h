#pragma once
#include "DxLib.h"

class Input;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player();
	~Player();
	void Init();
	void Update(Input& input);
	void Draw();

private:
	void Move(Input& input);	// プレイヤーの移動処理
	void Jump(Input& input);	// プレイヤーのジャンプ処理

private:
	VECTOR m_pos;		// プレイヤー位置
	VECTOR m_move;		// 移動量
	int m_jumpFrame;	// ジャンプフレーム
	bool m_isJump;		// ジャンプフラグ true:ジャンプ中
	int m_modelHandle;	// プレイヤーの3Dモデル

private:
	static constexpr float kScale = 0.1f;		// プレイヤーモデルの拡大率
	static constexpr float kMove = 1.0f;		// プレイヤー移動量
	static constexpr float kVelocity = 15.0f;	// ジャンプの高さ
	static constexpr float kGravity = -1.8f;	// 重力

	// ジャンプフレーム
	static constexpr int kLittleJumpFrame = 10;			// 小ジャンプ
	static constexpr int kMediumJumpFrame = 30;			// 中ジャンプ
	// ジャンプの高さ
	static constexpr float kLittleJumpHeight = 0.5f;	// 小ジャンプ
	static constexpr float kMediumJumpHeight = 0.8f;	// 中ジャンプ
	static constexpr float kBigJumpHeight = 1.0f;		// 大ジャンプ
};

