#include "ManagerResult.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
ManagerResult::ManagerResult():
	fp(nullptr)
{
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
	int milliSec = m_saveData.highScore * 1000 / 60;
	int sec = (milliSec / 1000) % 90;
	milliSec %= 1000;
	printfDx("�x�X�g�^�C��:%02d:%03d\n", sec, milliSec);

	milliSec = m_saveData.second * 1000 / 60;
	sec = (milliSec / 1000) % 90;
	milliSec %= 1000;
	printfDx("2��:%02d:%03d\n", sec, milliSec);

	milliSec = m_saveData.third * 1000 / 60;
	sec = (milliSec / 1000) % 90;
	milliSec %= 1000;
	printfDx("3��:%02d:%03d\n", sec, milliSec);
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