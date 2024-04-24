#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
#include <DxLib.h>

/// <summary>
/// クリアタイムの管理
/// </summary>
class ManagerResult
{
public:
	ManagerResult();
	~ManagerResult() {};
	void Load();	// ファイル読み込み
	void Save(int time);	// ファイル書き込み

	int GetClearTime() const { return m_saveData.clearTime; }

private:

	// セーブデータの構造体
	struct SaveData
	{
		int highScore = 8000;	// ハイスコア
		int second = 9000;		// 2位のタイム
		int third = 10000;		// 3位のタイム
		int clearTime = 0;		// クリアタイム
	};

	SaveData m_saveData;
	FILE *fp;
	const char *fileName = "saveData.dat";
};

