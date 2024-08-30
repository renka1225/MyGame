#include "DxLib.h"
#include "Text1.h"
#include <fstream>
#include <sstream>

// �萔
namespace
{
	const char* kFileName = "data/test.csv"; // �t�@�C����
	constexpr float kAmplitude = 8.0f;		 // �U�ꕝ
	constexpr float kCycle = 0.05f;			 // ����
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
Text1::Text1():
	m_textPosY(0),
	m_time(0)
{
	LoadCsv();
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
Text1::~Text1()
{
}


/// <summary>
/// ������
/// </summary>
void Text1::Init()
{
}


/// <summary>
/// �X�V
/// </summary>
void Text1::Update()
{
	m_time++;
}


/// <summary>
/// �`��
/// </summary>
void Text1::Draw()
{
	int x = 0;

	for (const auto& line : m_text)
	{
		m_textPosY = kAmplitude * sin(m_time * kCycle - (x / 40.0f));
		DrawString(x, 20 + m_textPosY, line.c_str(), 0xffffff);
		x += 10;
	}
}


/// <summary>
/// CSV�t�@�C������e�L�X�g��ǂݍ���
/// </summary>
void Text1::LoadCsv()
{
	std::ifstream file(kFileName);
	m_text.clear();
	std::string line;

	// �t�@�C���̓��͎擾
	// std::getline(�ǂݎ��t�@�C���̕ϐ�, ���͕�������i�[����ϐ�);
	while (std::getline(file, line))
	{
		std::istringstream stream(line);
		std::string field;

		// �����񕪊�
		// getline(istringstream�^�̕ϐ�, ����������������i�[����ϐ�, ',�ŕ���')
		while (getline(stream, field, ','))
		{
			for (char c : field)
			{
				std::string charStr(1, c);  // 1�����𕶎���ɕϊ�
				m_text.push_back(charStr);  // �������x�N�^�[�ɒǉ�
			}
		}
	}
}
