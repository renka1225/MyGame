#include "FontManager.h"
#include "DxLib.h"

FontManager::FontManager()
{
	/*�t�H���g*/
	// �t�@�C���̃��[�h
	LPCSTR font_path = "data/Kaisotai-Next-UP-B.otf";

	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0)
	{
	}
	else
	{
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}

	m_fontHandle = CreateFontToHandle("���z�� �l�N�X�g UP B", 28, -1);
	m_fontHandle2 = CreateFontToHandle("���z�� �l�N�X�g UP B", 36, -1);
	m_fontHandle3 = CreateFontToHandle("���z�� �l�N�X�g UP B", 45, -1);
	m_fontStaging = CreateFontToHandle("���z�� �l�N�X�g UP B", 85, -1);
}

FontManager::~FontManager()
{
	DeleteFontToHandle(m_fontHandle);
	DeleteFontToHandle(m_fontHandle2);
	DeleteFontToHandle(m_fontHandle3);
	DeleteFontToHandle(m_fontStaging);
}
