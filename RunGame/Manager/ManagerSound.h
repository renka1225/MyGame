#pragma once

/// <summary>
/// �T�E���h�Ǘ��N���X
/// </summary>
class ManagerSound
{
public:
	ManagerSound();
	~ManagerSound();

	int GetStartCountSE() const { return m_startCountSE; }

private:
	int m_gameBgm;		// �v���C����BGM
	int m_selectSE;		// �I������SE

	int m_startCountSE;	// �X�^�[�g�J�E���g��SE
};

