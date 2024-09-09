#pragma once

/// <summary>
/// �t�H���g�Ǘ��N���X
/// </summary>
class FontManager
{
public:
	FontManager();
	~FontManager();

	// �t�H���g���擾
	int GetFont() const { return m_fontHandle; }
	int GetFont2() const { return m_fontHandle2; }
	int GetFont3() const { return m_fontHandle3; }
	int GetFontStaging() const { return m_fontStaging; }

private:
	int m_fontHandle;
	int m_fontHandle2;
	int m_fontHandle3;
	int m_fontStaging; // ���o�p�̃t�H���g
};

