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
	int GetCount3SE() const { return m_count3SE; }
	int GetCount2SE() const { return m_count2SE; }
	int GetCount1SE() const { return m_count1SE; }
	int GetNoticeSE() const { return m_noticeSE; }
	int GetJumpSE() const { return m_jumpSE; }
	int GetTitleBgm() const { return m_titleBgm; }
	int GetPlayBgm() const { return m_playBgm; }
	int GetGameoverBgm() const { return m_gameoverBgm; }
	int GetClearBgm() const { return m_clearBgm; }

private:
	int m_selectSE;		// �I������SE
	int m_determineSE;	// ���莞��SE

	// �X�^�[�g�J�E���g��SE
	int m_count3SE;
	int m_count2SE;
	int m_count1SE;


	int m_noticeSE;		// �ʒm�\������SE
	int m_jumpSE;		// �W�����v��SE

	int m_titleBgm;		// �^�C�g��BGM
	int m_playBgm;		// �v���C��BGM
	int m_gameoverBgm;	// �Q�[���I�[�o�[BGM
	int m_clearBgm;		// �N���ABGM
};

