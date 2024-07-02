#pragma once
#include <vector>

/// <summary>
/// ��������쐬����
/// </summary>
namespace Confetti
{
	void CreateCofetti();	// �쐬
	void DeleteCofetti();	// �폜
	void UpdateCofetti();	// �X�V
	void DrawCofetti();		// �`��

	struct ConfettiInfo
	{
		int x;		// X���W
		int y;		// Y���W
		int size;	// �T�C�Y
		int speed;	// �������x
		int color;	// �F
	};

	extern std::vector<ConfettiInfo> confettis;
}
