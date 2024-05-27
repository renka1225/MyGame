#pragma once
#include "DxLib.h"
#include "MyLib.h"
#include <memory>

class Collidable;
class Physics;
class Stage;
class Input;
class DrawDebug;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player : public Collidable
{
public:
	Player(std::shared_ptr<Physics> physics);
	virtual ~Player();
	void Init();
	void End();
	void Update(Input& input, Stage& stage);
	void Draw(DrawDebug& drawDebug);
	void OnCollide();	// 衝突したとき

	void SetCameraAngle(float angle) { m_cameraAngle = angle; }

	VECTOR GetPos() const { return m_pos; }

private:
	void Move(Input& input);			// プレイヤーの移動処理
	void Jump(Input& input);			// プレイヤーのジャンプ処理
	void UpdateAngle(Stage& stage);		// プレイヤーの傾きを調整する
	float GroundHeight(Stage& stage);	// 地面の高さを計算する

private:
	std::shared_ptr<Physics> m_pPhysics;

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
	static constexpr float kVelocity = 15.0f;	// ジャンプの高さ
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

