#include "ManagerResult.h"


/// <summary>
/// コンストラクタ
/// </summary>
ManagerResult::ManagerResult():
	fp(nullptr)
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

	m_saveData.clearTime = time;	// クリアタイム更新

#ifdef _DEBUG
	// 経過時間の描画
	int milliSec = m_saveData.highScore * 1000 / 60;
	int sec = (milliSec / 1000) % 90;
	milliSec %= 1000;
	printfDx("ベストタイム:%02d:%03d\n", sec, milliSec);

	milliSec = m_saveData.second * 1000 / 60;
	sec = (milliSec / 1000) % 90;
	milliSec %= 1000;
	printfDx("2位:%02d:%03d\n", sec, milliSec);

	milliSec = m_saveData.third * 1000 / 60;
	sec = (milliSec / 1000) % 90;
	milliSec %= 1000;
	printfDx("3位:%02d:%03d\n", sec, milliSec);
#endif

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