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

private:
	int m_fontHandle;
};

