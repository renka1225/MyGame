#pragma once
#include <vector>

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
		kSize42_4,
		kSize32_4,
		kSize24_4,
		kSize16_4,
		kNormal,
		kNum,		// �t�H���g�̎�ނ̐�

		// �g���t�H���g���w�肷��
		// SceneTitle
		kTitleMenu = kSize64_4,

		// ScenePlaying
		kOption = kSize24_4,
		kPauseMenu = kSize42_4,
		kMenuTitle = kSize42_4,

		// SceneClear
		kClearMenu = kSize42_4,
	};

	// �t�H���g�̃��[�h�A�A�����[�h
	void Load();
	void UnLoad();

	// �t�H���g�̃n���h��
	// MEMO:extern���g�p���ĈقȂ�\�[�X�t�@�C���ŕϐ������L�ł���悤�ɂ���
	extern std::vector<int> m_fontHandle;
}

