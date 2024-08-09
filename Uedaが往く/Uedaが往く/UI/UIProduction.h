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
	// ���������\��
	void DrawOperation();

private:
	int m_fightTextHandle;	// "Fight"�̃e�L�X�g�摜
	int m_numTextHandle;	// �����̉摜

	// �{�^���̎��
	enum Button
	{
		kLSButton = 0,	// �����̃A�i���O�X�e�B�b�N
		kRSButton = 1,	// �E���̃A�i���O�X�e�B�b�N
		kAButton = 4,	// A�{�^��
		kBButton = 10,	// B�{�^��
		kXButton = 2,	// X�{�^��
		kYButton = 3,	// Y�{�^��
		kLBButton = 5,	// LB�{�^��
		kRBButton = 6,	// RB�{�^��
		kLineButton = 7,// �O�{���{�^��
		kViewButton = 8,// �r���[�{�^�� 
		kButtonNum = 9	// �{�^���̐�
	};

};

