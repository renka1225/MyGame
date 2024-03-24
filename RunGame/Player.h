#pragma once
#include "Rect.h"
#include "DxLib.h"
#include <memory>

class Input;
class ManagerModel;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player(std::shared_ptr<ManagerModel> pModel);
	virtual ~Player();
	void Init();
	void Update(Input& input);
	void Draw();
	void End();

	VECTOR GetPos() const { return m_pos; }			// 現在位置を取得
	Rect GetColRect() const { return m_colRect; }	// 当たり判定を取得する

private:
	// ジャンプ処理
	void Jump(Input& input);

private:
	// モデルクラスのポインタ
	std::shared_ptr<ManagerModel> m_pModel;

	// 表示位置
	VECTOR m_pos;
	// 移動量
	VECTOR m_move;
	// 当たり判定用の矩形
	Rect m_colRect;

	// ジャンプフラグ true:ジャンプ中
	bool m_isJump;
	// ジャンプフレーム
	int m_jumpFrame;

	// 3Dモデル
	int m_modelHandle;


private:	// 定数
	static constexpr float kMove = static_cast<float>(10000.0 / 60.0 / 60.0 / 60.0);	// 移動量
	static constexpr float kGravity = 0.5f;												// 重力
	static constexpr float kVelocity = 10.0f;											// 初速度
	static constexpr float kDirY = -90.0f * DX_PI_F / 180.0f;							// Y軸方向の向き
	static constexpr float kScale = 0.5f;												// プレイヤーのサイズ
	static constexpr int kWidth = 32;													// プレイヤーの横幅
	static constexpr int kHeight = 32;													// プレイヤーの高さ
	static constexpr float kGroundHeight = 0.0f;										// 地面の高さ

	// ジャンプフレーム
	static constexpr int kLittleJumpFrame = 10;		// 小ジャンプ
	static constexpr int kMediumJumpFrame = 30;		// 中ジャンプ
	// ジャンプの高さ
	static constexpr float kLittleJumpHeight = 0.5f;	// 小ジャンプ
	static constexpr float kMediumJumpHeight = 0.8f;	// 中ジャンプ
	static constexpr float kBigJumpHeight = 1.0f;		// 大ジャンプ
};