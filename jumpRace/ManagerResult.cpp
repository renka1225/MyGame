#include "ManagerResult.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
ManagerResult::ManagerResult()
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
		m_saveData.highScore = time;
	}
	else if (m_saveData.second > time)
	{
		m_saveData.second = time;
	}
	else if(m_saveData.third > time)
	{
		m_saveData.third = time;
	}

	m_saveData.clearTime = time;	// �N���A�^�C���X�V

	printfDx("�x�X�g�^�C��:%d, 2��:%d, 3��:%d", m_saveData.highScore, m_saveData.second, m_saveData.third);

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