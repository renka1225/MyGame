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

	m_fontHandle = CreateFontToHandle("Pomeranian", 28, -1);
	//m_startCountFontHandle = CreateFontToHandle("KyouryunoGuratan", 100, -1);
	//m_textFontHandle = CreateFontToHandle("KyouryunoGuratan", 60, -1);
	//m_timeFontHandle = CreateFontToHandle("KyouryunoGuratan", 60, -1);
	//m_creditFontHandle = CreateFontToHandle("KyouryunoGuratan", 24, -1);
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
ManagerFont::~ManagerFont()
{
	DeleteFontToHandle(m_fontHandle);
	//DeleteFontToHandle(m_startCountFontHandle);
	//DeleteFontToHandle(m_textFontHandle);
	//DeleteFontToHandle(m_timeFontHandle);
	//DeleteFontToHandle(m_creditFontHandle);
}
