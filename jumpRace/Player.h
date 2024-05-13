#pragma once
#include "DxLib.h"
#include <memory>

class ManagerModel;
class WorldSprite;
class Input;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player(std::shared_ptr<ManagerModel> pModel);
	~Player();
	void Init();
	void Update(Input& input);
	void Draw();

	void Move();			// プレイヤーを移動させる
	void ClearStaging();	// クリア時の演出

	VECTOR GetPos() const { return m_pos; }

private:
	std::shared_ptr<ManagerModel> m_pModel;

	VECTOR m_pos;	// 位置

	// クリア時のプレイヤー情報
	MATRIX m_modelMtx;
	MATRIX m_rotMtx;
	VECTOR m_move;
	float m_angle;			// 向いている方向
	float m_cameraAngle;	// カメラの向いている方向

	int m_isClear;	// クリアしたかのフラグ

	int m_model;	// 3Dモデル

private:	// 定数
	static constexpr float kScale = 0.3f;		// プレイヤーのサイズ
	static constexpr float kJumpHeight = 40.0f;	// ジャンプの高さ
	static constexpr float kMoveZ = -3.0f;		// Z軸の移動量
	static constexpr float kGravity = -3.5f;	// 重力
	static constexpr float kInitPosX = 10.0f;	// 初期位置X
	static constexpr float kInitPosY = 10.0f;	// 初期位置Y
	static constexpr float kInitPosZ = 20.0f;	// 初期位置Z

	static constexpr int kShadowPosX = 640;		// 影の表示位置X
	static constexpr int kShadowPosY = 600;		// 影の表示位置Y
	static constexpr int kShadowRadius = 25;	// 影の半径

	// クリア演出時
	static constexpr float kClearInitPosX = 5.0f;		// クリア時のX座標
	static constexpr float kClearInitPosZ = -80.0f;		// クリア時のZ座標
	static constexpr float kClearEndPosX = -5.0f;		// 移動できるX座標の範囲
	static constexpr float kClearEndPosZ = -100.0f;		// 移動できるZ座標の範囲
	static constexpr float kClearMove = -0.1f;			// 移動量
	static constexpr float kRotRad = 0.1f;				// 毎フレームの回転角度
};