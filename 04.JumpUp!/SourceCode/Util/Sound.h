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
		kRunSE,			// �ړ�
		kJumpSE,		// �W�����v
		kClearSE,		// �N���A����SE
		kClearCheersSE, // �N���A���̊�����SE
		kTitleBGM,		// �^�C�g��
		kPlayBGM,		// �v���C��
		kClearBGM,		// �N���A
		kNum			// �T�E���h�̐�
	};

	void Load();
	void UnLode();
	void ChangeVol(); // ���ʂ�ύX����

	extern std::vector<int> m_soundHandle;
};

