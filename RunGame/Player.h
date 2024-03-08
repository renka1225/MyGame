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
	virtual ~Player();
	void Init();
	void Update(Input& input);
	void Draw();
	void End();

private:
	// 位置
	VECTOR m_pos;
	// モデル
	int m_handle;
};