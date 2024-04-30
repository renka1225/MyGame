#include "ManagerResult.h"
#include "ConversionTime.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
ManagerResult::ManagerResult():
	fp(nullptr)
{
	m_pConversionTime = std::make_shared<ConversionTime>();
}


/// <summary>
/// �t�@�C���̓ǂݍ���
/// </summary>
void ManagerResult::Load()
{
	if (fopen_s(&fp, fileName, "rb") != 0)
	{
		printfDx("�t�@�C���ǂݍ��ݎ��s\n");
	}
	else
	{
		// �t�@�C������f�[�^��ǂݍ���
		fread(&m_saveData, sizeof(SaveData), 1, fp);
		fclose(fp);
	}
}


/// <summary>
/// �t�@�C���ɏ�������
/// </summary>
void ManagerResult::Save(int time)
{
	// �n�C�X�R�A�X�V
	if (m_saveData.highScore > time)
	{
		m_saveData.third = m_saveData.second;
		m_saveData.second = m_saveData.highScore;
		m_saveData.highScore = time;
	}
	else if (m_saveData.second > time)
	{
		m_saveData.third = m_saveData.second;
		m_saveData.second = time;
	}
	else if(m_saveData.third > time)
	{
		m_saveData.third = time;
	}

	m_saveData.clearTime = time;	// �N���A�^�C���X�V

#ifdef _DEBUG
	// �o�ߎ��Ԃ̕`��
	m_pConversionTime->Change(m_saveData.highScore);
	printfDx("�x�X�g�^�C��:%02d:%03d\n", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());

	m_pConversionTime->Change(m_saveData.second);
	printfDx("2��:%02d:%03d\n", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());

	m_pConversionTime->Change(m_saveData.third);
	printfDx("3��:%02d:%03d\n", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());
#endif

	if (fopen_s(&fp, fileName, "wb") != 0)
	{
		printfDx("�t�@�C���I�[�v���G���[\n");
	}
	else
	{
		fwrite(&m_saveData, sizeof(SaveData), 1, fp);
		fclose(fp);
	}
}