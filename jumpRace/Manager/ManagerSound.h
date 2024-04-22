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
	int GetStartCountSE() const { return m_startCountSE; }
	int GetNoticeSE() const { return m_noticeSE; }
	int GetJumpSE() const { return m_jumpSE; }
	int GetDamageSE() const { return m_damageSE; }
	int GetTitleBgm() const { return m_titleBgm; }
	int GetPlayBgm() const { return m_playBgm; }
	int GetGameoverBgm() const { return m_gameoverBgm; }
	int GetClearBgm() const { return m_clearBgm; }

private:
	int m_selectSE;		// �I������SE
	int m_determineSE;	// ���莞��SE
	int m_startCountSE;	// �X�^�[�g�J�E���g��SE
	int m_noticeSE;		// �ʒm�\������SE
	int m_jumpSE;		// �W�����v��SE
	int m_damageSE;		// �G�ɓ��������ۂ�SE

	int m_titleBgm;		// �^�C�g��BGM
	int m_playBgm;		// �v���C��BGM
	int m_gameoverBgm;	// �Q�[���I�[�o�[BGM
	int m_clearBgm;		// �N���ABGM
};

