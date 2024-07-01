#pragma once
#include <vector>

/// <summary>
/// ��������쐬����
/// </summary>
namespace Confetti
{
	void CreateCofetti();	// ������̍쐬
	void UpdateCofetti();	// ������̍X�V
	void DrawCofetti();		// ������̕`��

	struct ConfettiInfo
	{
		int x;		// X���W
		int y;		// Y���W
		int size;	// �T�C�Y
		int speed;	// �������x
		int color;	// �F
	};
	ConfettiInfo confettiInfo;

	extern std::vector<ConfettiInfo> confettis;
}
