#include "ManagerResult.h"
#include "ConversionTime.h"


/// <summary>
/// コンストラクタ
/// </summary>
ManagerResult::ManagerResult():
	fp(nullptr)
{
	m_pConversionTime = std::make_shared<ConversionTime>();
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
	m_pConversionTime->Change(m_saveData.highScore);
	printfDx("ベストタイム:%02d:%03d\n", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());

	m_pConversionTime->Change(m_saveData.second);
	printfDx("2位:%02d:%03d\n", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());

	m_pConversionTime->Change(m_saveData.third);
	printfDx("3位:%02d:%03d\n", m_pConversionTime->GetSec(), m_pConversionTime->GetMilliSec());
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