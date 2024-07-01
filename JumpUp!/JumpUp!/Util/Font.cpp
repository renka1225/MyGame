#include "DxLib.h"
#include "Font.h"

namespace
{
	// �ǂݍ��ރt�H���g�t�@�C����
	const LPCSTR kFontDataPath[] =
	{
		"data/font/TsunagiGothic.ttf",
	};

	// �t�H���g�̃f�[�^
	struct FontData
	{
		const char* name;	// �t�H���g��
		int size;			// �t�H���g�T�C�Y
		int thick;			// �t�H���g�̑���(-1:�f�t�H���g)
		int type;			// �t�H���g�̃^�C�v(-1:�f�t�H���g)
	};
}

namespace Font
{
	std::vector<int> m_fontHandle;

	FontData data[] =
	{
		// Size96_4
		{"Tsunagi Gothic Black", 96, 4, -1},
		// Size64_4
		{"Tsunagi Gothic Black", 64, 4, -1},
		// Size48_4
		{"Tsunagi Gothic Black", 48, 4, -1},
		// Size42_4
		{"Tsunagi Gothic Black", 42, 4, -1},
		// Size40_4
		{"Tsunagi Gothic Black", 40, 4, DX_FONTTYPE_ANTIALIASING_EDGE_8X8},
		// Size28_4
		{"Tsunagi Gothic Black", 28, 4, -1},
		// Size24_4
		{"Tsunagi Gothic Black", 24, 4, -1},
		// Size16_4
		{"Tsunagi Gothic Black", 16, 4, -1},
		// Normal
		{"�l�r�@�S�V�b�N", 16, -1, -1},
	};


	/// <summary>
	/// �t�H���g�̃��[�h
	/// </summary>
	void Font::Load()
	{
		Font::m_fontHandle.resize(static_cast<int>(Font::FontId::kNum));

		for (auto& fontPath : kFontDataPath)
		{
			if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0) {
			}
			else
			{
				// �t�H���g�Ǎ��G���[����
				MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
			}
		}

		// �t�H���g�f�[�^����
		for (int i = 0; i < Font::m_fontHandle.size(); i++)
		{
			Font::m_fontHandle[i] = CreateFontToHandle(data[i].name, data[i].size, data[i].thick, data[i].type);
		}
	}


	/// <summary>
	/// �t�H���g�̃A�����[�h
	/// </summary>
	void Font::UnLoad()
	{
		for (auto& fontPath : kFontDataPath)
		{
			if (RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL))
			{
			}
			else
			{
				MessageBox(NULL, "�t�H���g�폜���s", "", MB_OK);
			}
		}

		// �t�H���g�f�[�^�폜
		for (const auto& handle : m_fontHandle)
		{
			DeleteFontToHandle(handle);
		}
	}
}
