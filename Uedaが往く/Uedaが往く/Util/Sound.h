#pragma once
#include <vector>

/// <summary>
/// �T�E���h�Ǘ�
/// </summary>
namespace Sound
{
	// �T�E���h�̎��
	enum class SoundKind
	{
		kCursorSE,		// �J�[�\���ړ�
		kSelectSE,		// ����
		kAttackSE,		// �U��
		kClearCheersSE, // �N���A���̊���SE
		kTitleBGM,		// �^�C�g��BGM
		kStageSelectBGM,// �X�e�[�W�I��BGM
		kStage1BGM,		// �X�e�[�W1BGM
		kStage2BGM,		// �X�e�[�W2BGM
		kClearBGM,		// �N���ABGM
		kGameoverBGM,	// �Q�[���I�[�o�[BGM
		kNum			// �T�E���h�̐�
	};

	void Load();
	void UnLode();
	void ChangeVol(); // ���ʂ�ύX����

	extern std::vector<int> m_soundHandle;
};

