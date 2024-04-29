#pragma once
#include "DxLib.h"
#include <memory>

class ManagerModel;
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

	void Move();	// プレイヤーを移動させる

	VECTOR GetPos() const { return m_pos; }

private:
	std::shared_ptr<ManagerModel> m_pModel;

	VECTOR m_pos;	// 位置
	int m_model;	// 3Dモデル

private:	// 定数
	static constexpr float kScale = 0.3f;		// プレイヤーのサイズ
	static constexpr float kJumpHeight = 40.0f;	// ジャンプの高さ
	static constexpr float kMoveZ = -3.0f;		// Z軸の移動量
	static constexpr float kGravity = -5.0f;	// 重力
	static constexpr float kInitPosX = 10.0f;	// 初期位置X
	static constexpr float kInitPosY = 10.0f;	// 初期位置Y
	static constexpr float kInitPosZ = 20.0f;	// 初期位置Z
};