#pragma once

/// <summary>
/// �v���C���[�N���X
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
	// �ʒu
	VECTOR m_pos;
	// ���f��
	int m_handle;
};