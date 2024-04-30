#pragma once
#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <memory>


class ConversionTime;

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

	int GetClearTime() const { return m_saveData.clearTime; }	// �N���A�^�C���擾
	int GetHighScore() const { return m_saveData.highScore; }	// �n�C�X�R�A�擾
	int GetSecond() const { return m_saveData.second; }	// 2�ʂ̃^�C���擾
	int GetThird() const { return m_saveData.third; }		// 3�ʂ̃^�C���擾

private:
	std::shared_ptr<ConversionTime> m_pConversionTime;

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

