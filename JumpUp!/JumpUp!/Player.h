#pragma once
#include "DxLib.h"
#include "Collidable.h"
#include <memory>

class Collidable;
class Stage;
class Input;
class DrawDebug;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player : public Collidable
{
public:
	Player();
	virtual ~Player();
	void Init(std::shared_ptr<Physics> physics);
	void Final(std::shared_ptr<Physics> physics);
	void Update(Input& input, Stage& stage);
	void Draw(DrawDebug& drawDebug);
	virtual void OnCollide() override;	// 衝突したとき

	void SetCameraAngle(float angle) { m_cameraAngle = angle; }

	VECTOR GetPos() const { return m_pos; }

private:
	void Move(Input& input);			// プレイヤーの移動処理
	void Jump(Input& input);			// プレイヤーのジャンプ処理
	void UpdateAngle(Stage& stage);		// プレイヤーの傾きを調整する
	float FixPosY(Stage& stage);		// 地面の位置からプレイヤーのY座標の位置を求める
	bool HitStage(Stage& stage);		// ステージとの当たり判定

private:

	// プレイヤー情報
	VECTOR m_pos;		// プレイヤー位置
	VECTOR m_move;		// 移動量
	float m_angle;		// 向いている方向
	int m_jumpFrame;	// ジャンプフレーム
	bool m_isJump;		// ジャンプフラグ true:ジャンプ中
	int m_modelHandle;	// プレイヤーの3Dモデル

	// カメラ情報
	float m_cameraAngle;

private:	// 定数
	// プレイヤーの情報
	static constexpr float kScale = 0.1f;		// プレイヤーモデルの拡大率
	static constexpr float kMove = 1.0f;		// プレイヤー移動量
	static constexpr float kVelocity = 20.0f;	// ジャンプの高さ
	static constexpr float kGravity = -1.5f;	// 重力

	// 当たり判定
	static constexpr float kCenterPosY = 12.0f;	// プレイヤーの中心点を調整
	static constexpr float kWidth = 10.0f;		// 横幅
	static constexpr float kHeight = 24.0f;		// 縦幅
	static constexpr float kDepth = 5.0f;		// 奥行きの幅

	// ジャンプフレーム
	static constexpr int kLittleJumpFrame = 10;			// 小ジャンプ
	static constexpr int kMediumJumpFrame = 30;			// 中ジャンプ
	// ジャンプの高さ
	static constexpr float kLittleJumpHeight = 0.5f;	// 小ジャンプ
	static constexpr float kMediumJumpHeight = 0.8f;	// 中ジャンプ
	static constexpr float kBigJumpHeight = 1.0f;		// 大ジャンプ
};

