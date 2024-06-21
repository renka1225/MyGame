#include "DxLib.h"
#include "Font.h"
#include <vector>

namespace
{
	// �ǂݍ��ރt�H���g�t�@�C����
	const LPCSTR kFontDataPath[] =
	{
		"data/Font/TsunagiGothic.ttf",
	};

	// �t�H���g�̃f�[�^
	struct FontData
	{
		const char* name;	// �t�H���g��
		int size;			// �t�H���g�T�C�Y
		int thick;			// �t�H���g�̑���(-1:�f�t�H���g)
		int type;			// �t�H���g�̃^�C�v(-1:�f�t�H���g)
	};

	// �t�H���g�̃n���h��
	std::vector<int> fontHandle(static_cast<int>(Font::FontId::kNum));

	constexpr FontData data[] =
	{
		// Size96_4
		{
			"Tsunagi Gothic Black",
			96,
			4,
			-1
		},
		// Size64_4
		{
			"Tsunagi Gothic Black",
			64,
			4,
			-1
		},
		// Size48_4
		{
			"Tsunagi Gothic Black",
			48,
			4,
			-1
		},
		// Size32_4
		{
			"Tsunagi Gothic Black",
			32,
			4,
			-1
		},
		// Size24_4
		{
			"Tsunagi Gothic Black",
			24,
			4,
			-1
		},
		// Size16_4
		{
			"Tsunagi Gothic Black",
			16,
			4,
			-1
		},
		// Normal
		{
			"�l�r�@�S�V�b�N",
			16,
			-1,
			-1
		},
	};
}

namespace Font
{
	/// <summary>
	/// �t�H���g�̃��[�h
	/// </summary>
	void Font::Load()
	{
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
		for (int i = 0; i < static_cast<int>(Font::FontId::kNum); i++)
		{
			fontHandle[i] = CreateFontToHandle(data[i].name, data[i].size, data[i].thick, data[i].type);
		}
	}


	/// <summary>
	/// �t�H���g�̃A�����[�h
	/// </summary>
	void Font::UnLoad()
	{
		// �t�H���g�̃A�����[�h
		for (auto& fontPath : kFontDataPath)
		{
			if (RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL)) {
			}
			else {
				MessageBox(NULL, "remove failure", "", MB_OK);
			}
		}
	}
}
