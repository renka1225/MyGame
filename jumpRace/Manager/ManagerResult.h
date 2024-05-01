#pragma once
#include "DxLib.h"
#include <memory>
#include <vector>

class ConversionTime;

/// <summary>
/// �N���A�^�C���̓ǂݏ���
/// </summary>
class ManagerResult
{
public:
	ManagerResult();
	~ManagerResult() {};
	void Load();	// �t�@�C���ǂݍ���
	void Save(int time);	// �t�@�C����������

	int GetClearTime() const { return m_clearTime; }			// �N���A�^�C���擾
	std::vector<int> GetRanking() const { return m_ranking; }	// �����L���O�擾

private:
	std::shared_ptr<ConversionTime> m_pConversionTime;	// �^�C���ɕϊ�����

	// �����L���O
	std::vector<int> m_ranking = {8000, 9000, 10000, 11000, 12000, 
								13000, 14000, 15000, 16000, 17000};
	// �N���A�^�C��
	int m_clearTime;

private:
	const char* fileName = "saveData.bin";	//�@�t�@�C����
	static constexpr int kRankingNum = 10;	// �ۑ����鏇�ʐ�
};