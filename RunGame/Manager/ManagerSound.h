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

private:
	int m_selectSE;		// �I������SE
	int m_determineSE;	// ���莞��SE
	int m_startCountSE;	// �X�^�[�g�J�E���g��SE

	int m_gameBgm;		// �v���C����BGM
};

