#pragma once
#include "DxLib.h"

class Input;

/// <summary>
/// �v���C���[�N���X
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
	// �ʒu
	VECTOR m_pos;
	// ���f��
	int m_handle;
};