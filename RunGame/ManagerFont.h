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

private:
	int m_fontHandle;
};

