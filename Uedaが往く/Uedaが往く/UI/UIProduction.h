#pragma once

/// <summary>
/// ���o�֘A��UI
/// </summary>
class UIProduction
{
public:
	UIProduction();
	~UIProduction();
	void Update();
	// �X�^�[�g���̉��o��\��
	void DrawStartProduction(int time, int matchNum, int maxMatch);

private:
	int m_fightTextHandle;	// "Fight"�̃e�L�X�g�摜
	int m_numTextHandle;	// �����̉摜
};

