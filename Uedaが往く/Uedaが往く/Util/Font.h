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
		kSize40_4,
		kSize28_4,
		kSize24_4,
		kSize16_4,
		kNormal,
		kNum,		// �t�H���g�̎�ސ�

		// �g���t�H���g���w�肷��
		// SceneSelectStage
		kSelectStage = kSize48_4, // �X�e�[�W�I���Ŏg�������T�C�Y
		// SceneOption
		kOption = kSize48_4,	  // �I�v�V�����Ŏg�p���镶���T�C�Y
		// ScenePause
		kPause = kSize42_4,		  // �|�[�Y��ʂŎg�p���镶���T�C�Y
		// SceneClear
		kClearTime = kSize42_4,	  // ���ԕ\���Ŏg�������T�C�Y
		// SceneGameover
		kGameover = kSize48_4,	  // �Q�[���I�[�o�[�Ŏg�������T�C�Y
		// �����L���O
		kRanking = kSize42_4,
		kRankingText = kSize48_4,
		//�E���ɕ\������{�^���\���̕����T�C�Y
		kButtonText = kSize42_4,
	};

	// �t�H���g�̃��[�h�A�A�����[�h
	void Load();
	void UnLoad();

	// �t�H���g�̃n���h��
	// MEMO:extern���g�p���ĈقȂ�\�[�X�t�@�C���ŕϐ������L�ł���悤�ɂ���
	extern std::vector<int> m_fontHandle;
}

