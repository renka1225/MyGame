#include "ManagerFont.h"
#include "DxLib.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ManagerFont::ManagerFont()
{
	// �t�@�C���̃��[�h
	LPCSTR fontPath = "data/font/Pomeranian-Regular.ttf";
	LPCSTR fontPath2 = "data/font/ChitoseGothic-Regular.otf";

	if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0 || AddFontResourceEx(fontPath2, FR_PRIVATE, NULL) > 0)
	{
	}
	else
	{
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}

	m_textFontHandle = CreateFontToHandle("Pomeranian", 30, -1);
	m_textFont2Handle = CreateFontToHandle("Pomeranian", 25, -1);
	m_startCountFontHandle = CreateFontToHandle("Chitose Gothic", 80, 6, DX_FONTTYPE_ANTIALIASING_EDGE);
	m_timeFontHandle = CreateFontToHandle("Chitose Gothic", 38, 8);
	m_resultFontHandle = CreateFontToHandle("Chitose Gothic", 40, -1);
	m_resultTimeFontHandle = CreateFontToHandle("Chitose Gothic", 30, -1);
	m_creditFontHandle = CreateFontToHandle("Pomerania", 15, -1);
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
ManagerFont::~ManagerFont()
{
	DeleteFontToHandle(m_textFontHandle);
	DeleteFontToHandle(m_textFont2Handle);
	DeleteFontToHandle(m_startCountFontHandle);
	DeleteFontToHandle(m_timeFontHandle);
	DeleteFontToHandle(m_resultFontHandle);
	DeleteFontToHandle(m_resultTimeFontHandle);
	DeleteFontToHandle(m_creditFontHandle);
}
