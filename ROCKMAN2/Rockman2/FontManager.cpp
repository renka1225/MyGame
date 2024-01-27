#include "FontManager.h"
#include "DxLib.h"

FontManager::FontManager()
{
	/*�t�H���g*/
// �t�@�C���̃��[�h
	LPCSTR font_path = "data/851Gkktt_005.ttf";	// �ǂݍ��ރt�H���g�t�@�C���̃p�X

	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0)
	{
	}
	else
	{
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}

	m_fontHandle = CreateFontToHandle("851�S�`�J�N�b�g", 30, -1);
}

FontManager::~FontManager()
{
	DeleteFontToHandle(m_fontHandle);
}
