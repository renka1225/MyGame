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

	void Move();	// プレイヤーを移動させる

	VECTOR GetPos() const { return m_pos; }

private:
	VECTOR m_pos;	// 位置
	int m_model;	// 3Dモデル

private:	// 定数
	static constexpr float kScale = 0.5f;							// プレイヤーのサイズ
	static constexpr float kMove = -3.0f;							// 移動量
	static constexpr float kInitPosX = 0.0f;						// 初期位置X
	static constexpr float kInitPosY = 10.0f;						// 初期位置Y
	static constexpr float kInitPosZ = 100.0f;						// 初期位置Z
};