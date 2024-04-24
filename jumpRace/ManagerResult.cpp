#include "ManagerResult.h"


/// <summary>
/// コンストラクタ
/// </summary>
ManagerResult::ManagerResult()
{
}


/// <summary>
/// ファイルの読み込み
/// </summary>
void ManagerResult::Load()
{
	if (fopen_s(&fp, fileName, "rb") != 0)
	{
		printfDx("ファイル読み込み失敗\n");
	}
	else
	{
		// ファイルからデータを読み込む
		fread(&m_saveData, sizeof(SaveData), 1, fp);
		fclose(fp);
	}
}


/// <summary>
/// ファイルに書き込み
/// </summary>
void ManagerResult::Save(int time)
{
	// ハイスコア更新
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

	m_saveData.clearTime = time;	// クリアタイム更新

	printfDx("ベストタイム:%d, 2位:%d, 3位:%d", m_saveData.highScore, m_saveData.second, m_saveData.third);

	if (fopen_s(&fp, fileName, "wb") != 0)
	{
		printfDx("ファイルオープンエラー\n");
	}
	else
	{
		fwrite(&m_saveData, sizeof(SaveData), 1, fp);
		fclose(fp);
	}
}