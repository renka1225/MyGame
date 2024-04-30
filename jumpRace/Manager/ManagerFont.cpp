#include "ManagerFont.h"
#include "DxLib.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ManagerFont::ManagerFont()
{
	// �t�@�C���̃��[�h
	LPCSTR font_path = "data/font/Pomeranian-Regular.ttf";

	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0)
	{
	}
	else
	{
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}

	m_textFontHandle = CreateFontToHandle("Pomeranian", 30, -1);
	m_startCountFontHandle = CreateFontToHandle("Pomerania", 100, -1);
	m_timeFontHandle = CreateFontToHandle("Pomerania", 35, -1);
	m_resultTimeFontHandle = CreateFontToHandle("Pomerania", 25, -1);
	m_creditFontHandle = CreateFontToHandle("Pomerania", 15, -1);
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
ManagerFont::~ManagerFont()
{
	DeleteFontToHandle(m_textFontHandle);
	DeleteFontToHandle(m_startCountFontHandle);
	DeleteFontToHandle(m_timeFontHandle);
	DeleteFontToHandle(m_resultTimeFontHandle);
	DeleteFontToHandle(m_creditFontHandle);
}
