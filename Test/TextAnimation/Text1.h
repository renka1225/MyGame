#pragma once
#include <vector>
#include <string>

class Text1
{
public:
	Text1();
	~Text1();
	void Init();
	void Update();
	void Draw();
	void LoadCsv(); // CSV�t�@�C����ǂݍ���

private:
	std::vector<std::string> m_text; // CSV�t�@�C������ǂݍ��񂾃e�L�X�g��ۑ�����
	float m_textPosY; // �e�L�X�g�ʒu
	int m_time;		  // �o�ߎ���
};

