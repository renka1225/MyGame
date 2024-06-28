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
		kCursorSE,	// �J�[�\���ړ�
		kSelectSE,	// ����
		kJumpSE,	// �W�����v
		kClearSE,	// �N���A����SE
		kTitleBGM,	// �^�C�g��
		kPlayBGM,	// �v���C��
		kClearBGM,	// �N���A
		kNum		// �T�E���h�̐�
	};

	void Load();
	void UnLode();

	extern std::vector<int> m_soundHandle;
};

