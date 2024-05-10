#pragma once

/// <summary>
/// �T�E���h�Ǘ��N���X
/// </summary>
class ManagerSound
{
public:
	ManagerSound();
	~ManagerSound();

	int GetCursorSE() const { return m_cursorSE; }
	int GetSelectSE() const { return m_selectSE; }
	int GetCountSE() const { return m_countSE; }
	int GetJumpSE() const { return m_jumpSE; }
	int GetMissSE() const { return m_missSE; }
	int GetClearSE() const { return m_clearSE; }
	int GetTitleBgm() const { return m_titleBgm; }
	int GetPlayBgm() const { return m_playBgm; }
	int GetClearStagingBgm() const { return m_clearStagingBgm; }
	int GetClearBgm() const { return m_clearBgm; }

private:
	int m_cursorSE;		// �J�[�\���ړ�����SE
	int m_selectSE;		// �I������SE
	int m_countSE;		// �X�^�[�g�J�E���g��SE
	int m_jumpSE;		// �W�����v��SE
	int m_missSE;		// �{�^�������~�X����SE
	int m_clearSE;		// �N���A����SE

	int m_titleBgm;			// �^�C�g��BGM
	int m_playBgm;			// �v���C��BGM
	int m_clearStagingBgm;	// �N���A���o����BGM
	int m_clearBgm;			// �N���ABGM
};

