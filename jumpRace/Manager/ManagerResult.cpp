#include "ManagerResult.h"
#include "ConversionTime.h"
#include <fstream>
#include <algorithm>


/// <summary>
/// �R���X�g���N�^
/// </summary>
ManagerResult::ManagerResult():
	m_clearTime(0)
{
	m_pConversionTime = std::make_shared<ConversionTime>();
}


/// <summary>
/// �t�@�C���ǂݍ���
/// </summary>
void ManagerResult::Load()
{
	std::fstream file;
	file.open(fileName, std::ios::in | std::ios::binary);
	if (!file.is_open()) // �t�@�C���ǂݍ��ݎ��s
	{
		printfDx("�t�@�C���ǂݍ��ݎ��s\n");
	}
	else // �t�@�C���ǂݍ��ݐ���
	{
		// �N���A�^�C���̓ǂݍ���
		file.read(reinterpret_cast<char*>(&m_clearTime), sizeof(int));

		// �����L���O�̓ǂݍ���
		m_ranking.clear(); // ���łɗv�f������ꍇ�̓N���A����
		for (int i = 0; i < kRankingNum; ++i)
		{
			int temp;
			file.read(reinterpret_cast<char*>(&temp), sizeof(int));
			m_ranking.push_back(temp);
		}
		file.close();
	}
}


/// <summary>
/// �t�@�C����������
/// </summary>
void ManagerResult::Save(int time)
{
	// �N���A�^�C���������L���O���ɓ����Ă���ꍇ�����L���O���X�V����
	auto it = std::find_if(m_ranking.begin(), m_ranking.end(), [time](int t) { return t > time; });
	if (it != m_ranking.end())
	{
		m_ranking.insert(it, time);
		// 10�ʈȏ�ۑ�����Ȃ��悤�ɂ���
		if (m_ranking.size() > kRankingNum)
		{
			m_ranking.resize(kRankingNum);
		}
	}
	else
	{
		m_ranking.push_back(time);
	}

	// ���ʂ������ɂ���
	std::sort(m_ranking.begin(), m_ranking.end(), [](int a, int b) { return a < b; });
	// �N���A�^�C�����X�V����
	m_clearTime = time;

	// �t�@�C���ɏ�������
	std::fstream file;
	file.open(fileName, std::ios::out | std::ios::binary);
	if (!file.is_open())	// �t�@�C���ǂݍ��ݎ��s��
	{
		printfDx("�t�@�C���������ݎ��s\n");
	}
	else	// �t�@�C���ǂݍ��ݐ���
	{
		file.write(reinterpret_cast<char*>(&m_clearTime), sizeof(int));

		// �����L���O�̏�������
		for (int i = 0; i < kRankingNum; ++i)
		{
			file.write(reinterpret_cast<char*>(&m_ranking[i]), sizeof(int));
		}
		file.close();
	}
}