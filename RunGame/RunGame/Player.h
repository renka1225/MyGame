#pragma once

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player();
	virtual ~Player();
	void Init();
	void Update();
	void Draw();
	void End();

private:
	// 位置
	VECTOR m_pos;
	// モデル
	int m_handle;
};