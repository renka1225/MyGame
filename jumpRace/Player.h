#pragma once

class Input;

/// <summary>
/// �v���C���[�N���X
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