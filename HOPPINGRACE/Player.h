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
	void Init() {};
	void Update(Input& input);
	void Draw();

	void Move();			// プレイヤーを移動させる
	void ClearStaging();	// クリア時の演出

	VECTOR GetPos() const { return m_pos; }		// プレイヤーの位置を取得
	VECTOR GetMove() const { return m_move; }	// プレイヤーの移動量を取得

private:
	std::shared_ptr<ManagerModel> m_pModel;

	// プレイヤー情報
	VECTOR m_pos;	// プレイヤー位置
	VECTOR m_move;	// 移動量

	int m_model;	// 3Dモデル

	// クリア時の情報
	int m_isClear;			// クリアしたかのフラグ
	int m_clearStagingTime;	// クリア演出の時間
	float m_angle;			// プレイヤーが向いている方向

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
	static constexpr int kClearStagingStartTime = 60;	// クリア演出開始時間
	static constexpr float kClearInitPosX = 0.0f;		// クリア時のX座標
	static constexpr float kClearInitPosZ = -80.0f;		// クリア時のZ座標
	static constexpr float kClearMoveX = 0.5f;			// X方向の移動量
	static constexpr float kClearMoveZ = 0.1f;			// Z方向の移動量
	static constexpr float kRotRad = 6.0f;				// 毎フレームの回転角度
	static constexpr int kJumpFrame = 20;				// ジャンプフレーム
};