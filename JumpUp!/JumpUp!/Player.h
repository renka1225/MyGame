#pragma once
#include "DxLib.h"

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw();

private:
	VECTOR m_pos;		// プレイヤー位置
	VECTOR m_move;		// 移動量
	int m_modelHandle;	// プレイヤーの3Dモデル

private:
	static constexpr float kScale = 0.1f;	// プレイヤーモデルの拡大率
};

