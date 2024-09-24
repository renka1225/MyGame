#pragma once
#include "Rect.h"
#include "DxLib.h"
#include <memory>

class Input;
class ManagerModel;
class ManagerSound;
class Map;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player(std::shared_ptr<ManagerModel> pModel, std::shared_ptr<ManagerSound> pSound, std::shared_ptr<Map> pMap);
	virtual ~Player();
	void Init() {};
	void Update(Input& input);
	void Draw();

	VECTOR GetPos() const { return m_pos; }			// 現在位置を取得
	Rect GetColRect() const { return m_colRect; }	// 当たり判定を取得する

private:
	void Jump(Input& input);	// ジャンプ処理

private:
	std::shared_ptr<ManagerModel> m_pModel;	// モデルクラスのポインタ
	std::shared_ptr<ManagerSound> m_pSound;	// サウンドクラスのポインタ
	std::shared_ptr<Map> m_pMap;			// マップクラスのポインタ

	VECTOR m_pos;		// 表示位置
	VECTOR m_move;		// 移動量
	Rect m_colRect;		// 当たり判定用の矩形

	bool m_isJump;		// ジャンプフラグ true:ジャンプ中
	int m_jumpFrame;	// ジャンプフレーム

	int m_modelHandle;	// プレイヤーの3Dモデル


private:	// 定数
	static constexpr float kMove = 0.07f;						// 移動量
	static constexpr float kGravity = 0.5f;						// 重力
	static constexpr float kVelocity = 8.3f;					// 初速度
	static constexpr float kDirY = -90.0f * DX_PI_F / 180.0f;	// Y軸方向の向き
	static constexpr float kScale = 0.3f;						// プレイヤーのサイズ
	static constexpr int kWidth = 90;							// プレイヤーの横幅
	static constexpr int kHeight = 90;							// プレイヤーの縦幅
	static constexpr float kColPosAdjustment = 5.0f;			// 当たり判定位置調整
	static constexpr float kInitPosX = 70.0f;					// 初期位置
	static constexpr float kGroundHeight = 0.0f;				// 地面の高さ

	// ジャンプフレーム
	static constexpr int kLittleJumpFrame = 10;			// 小ジャンプ
	static constexpr int kMediumJumpFrame = 30;			// 中ジャンプ
	// ジャンプの高さ
	static constexpr float kLittleJumpHeight = 0.5f;	// 小ジャンプ
	static constexpr float kMediumJumpHeight = 0.8f;	// 中ジャンプ
	static constexpr float kBigJumpHeight = 1.0f;		// 大ジャンプ
};