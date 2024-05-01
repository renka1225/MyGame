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
	int GetTextFont() const { return m_textFontHandle; }
	int GetTextFont2() const { return m_textFont2Handle; }
	int GetStartCountFont() const { return m_startCountFontHandle; }
	int GetTimeFont() const { return m_timeFontHandle; }
	int GetResultTimeFont() const { return m_resultTimeFontHandle; }
	int GetCreditFont() const { return m_creditFontHandle; }

private:
	int m_textFontHandle;		// �e�L�X�g�̃t�H���g
	int m_textFont2Handle;		// �e�L�X�g�̃t�H���g
	int m_startCountFontHandle;	// �X�^�[�g�J�E���g�̃t�H���g
	int m_timeFontHandle;		// ���Ԍo�߂̃t�H���g
	int m_resultTimeFontHandle;	// ���ʃ^�C���̃t�H���g
	int m_creditFontHandle;		// �N���W�b�g�\�L�̃t�H���g
};

