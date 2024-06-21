#pragma once

// �t�H���g�֘A
namespace Font
{

	// �t�H���g�̎��
	enum class FontId
	{
		// �t�H���g�T�C�Y�A����
		kSize96_4,
		kSize64_4,
		kSize48_4,
		kSize32_4,
		kSize24_4,
		kSize16_4,
		kNormal,
		kNum,		// �t�H���g�̎�ނ̐�

		// �g���t�H���g���w�肷��
		// SceneTitle
		TitleMenu = kSize48_4,

		// ScenePlaying

		// SceneClear
	};

	// �t�H���g�̃��[�h�A�A�����[�h
	void Load();
	void UnLoad();
}
