#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <DxLib.h>

/// <summary>
/// �N���A�^�C���̊Ǘ�
/// </summary>
class ManagerResult
{
public:
	ManagerResult();
	~ManagerResult() {};
	void Load();	// �t�@�C���ǂݍ���
	void Save(int time);	// �t�@�C����������

	int GetClearTime() const { return m_saveData.clearTime; }

private:

	// �Z�[�u�f�[�^�̍\����
	struct SaveData
	{
		int highScore = 8000;	// �n�C�X�R�A
		int second = 9000;		// 2�ʂ̃^�C��
		int third = 10000;		// 3�ʂ̃^�C��
		int clearTime = 0;		// �N���A�^�C��
	};

	SaveData m_saveData;
	FILE *fp;
	const char *fileName = "saveData.dat";
};

