#pragma once

/// <summary>
/// �t�H���g�Ǘ��N���X
/// </summary>
class ManagerFont
{
public:
	ManagerFont();
	~ManagerFont();

	// �t�H���g���擾
	int GetFont() const { return m_fontHandle; }
	int GetStartCountFont() const { return m_startCountFontHandle; }
	int GetTimeFont() const { return m_timeFontHandle; }
	int GetTextFont() const { return m_textFontHandle; }
	int GetCreditFont() const { return m_creditFontHandle; }

private:
	int m_fontHandle;
	int m_startCountFontHandle;	// �X�^�[�g�J�E���g�̃t�H���g
	int m_textFontHandle;		// �e�L�X�g�̃t�H���g
	int m_timeFontHandle;		// ���Ԍo�߂̃t�H���g
	int m_creditFontHandle;		// �N���W�b�g�̃t�H���g
};
