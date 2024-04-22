#pragma once

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
};