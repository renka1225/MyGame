#include "DxLib.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

namespace
{
	const char* const kFileName = "data/data.csv";
}

std::vector<float> m_data;

/// <summary>
/// �O���f�[�^�̓ǂݍ���
/// </summary>
void LoadData()
{
	std::ifstream file(kFileName);
	m_data.clear();
	std::string line;

	// �t�@�C���̓��͎擾
	// std::getline(�ǂݎ��t�@�C���̕ϐ�, ���͕�������i�[����ϐ�);
	while (std::getline(file, line))
	{
		std::istringstream stream(line);
		std::string field;

		// �����񕪊�
		// getline(istringstream�^�̕ϐ�, ����������������i�[����ϐ�, '���ŕ������邩')
		while (getline(stream, field, ','))
		{
			// �������float�ɕϊ�����m_data�ɒǉ�����
			try
			{
				m_data.push_back(std::stof(field));
			}
			catch (const std::invalid_argument& e)
			{
				// �����ȕ�������X�L�b�v
			}
		}
	}
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)	// �c�w���C�u��������������
	{
		return -1;
	}

	// �O���f�[�^�̓ǂݍ���
	LoadData();

	while (ProcessMessage() != -1)
	{
		// �ǂݍ��񂾃f�[�^��\������
		int y = 0;
		for (const auto& data : m_data)
		{
			DrawFormatString(0, y, 0xffffff, "%f:", data);
			y += 10;
		}

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();
	}

	DxLib_End();// �c�w���C�u�����g�p�̏I������

	return 0;	// �\�t�g�̏I�� 
}