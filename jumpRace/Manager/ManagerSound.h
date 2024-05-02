#pragma once

/// <summary>
/// �T�E���h�Ǘ��N���X
/// </summary>
class ManagerSound
{
public:
	ManagerSound();
	~ManagerSound();

	int GetSelectSE() const { return m_selectSE; }
	int GetDetermineSE() const { return m_determineSE; }
	int GetCountSE() const { return m_countSE; }
	int GetJumpSE() const { return m_jumpSE; }
	int GetMissSE() const { return m_missSE; }
	int GetTitleBgm() const { return m_titleBgm; }
	int GetPlayBgm() const { return m_playBgm; }
	int GetGameoverBgm() const { return m_gameoverBgm; }
	int GetClearBgm() const { return m_clearBgm; }

private:
	int m_selectSE;		// �I������SE
	int m_determineSE;	// ���莞��SE
	int m_countSE;		// �X�^�[�g�J�E���g��SE
	int m_jumpSE;		// �W�����v��SE
	int m_missSE;		// �{�^�������~�X����SE

	int m_titleBgm;		// �^�C�g��BGM
	int m_playBgm;		// �v���C��BGM
	int m_gameoverBgm;	// �Q�[���I�[�o�[BGM
	int m_clearBgm;		// �N���ABGM
};

