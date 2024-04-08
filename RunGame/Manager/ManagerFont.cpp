#include "ManagerFont.h"
#include "DxLib.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ManagerFont::ManagerFont()
{
	// �t�@�C���̃��[�h
	LPCSTR font_path = "data/font/KyouryunoGuratan.otf";

	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0)
	{
	}
	else
	{
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}

	m_fontHandle = CreateFontToHandle("KyouryunoGuratan", 28, -1);
	m_textFontHandle = CreateFontToHandle("KyouryunoGuratan", 60, -1);
	m_timeFontHandle = CreateFontToHandle("KyouryunoGuratan", 60, -1);
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
ManagerFont::~ManagerFont()
{
	DeleteFontToHandle(m_fontHandle);
	DeleteFontToHandle(m_textFontHandle);
	DeleteFontToHandle(m_timeFontHandle);
}
