#include "ManagerResult.h"
#include "ConversionTime.h"
#include <fstream>
#include <algorithm>


/// <summary>
/// コンストラクタ
/// </summary>
ManagerResult::ManagerResult():
	m_clearTime(0)
{
	m_pConversionTime = std::make_shared<ConversionTime>();
}


/// <summary>
/// ファイル読み込み
/// </summary>
void ManagerResult::Load()
{
	std::fstream file;
	file.open(fileName, std::ios::in | std::ios::binary);
	if (!file.is_open()) // ファイル読み込み失敗
	{
#ifdef _DEBUG
		printfDx("ファイル読み込み失敗\n");
#endif
	}
	else // ファイル読み込み成功
	{
		// クリアタイムの読み込み
		file.read(reinterpret_cast<char*>(&m_clearTime), sizeof(int));

		// ランキングの読み込み
		m_ranking.clear(); // すでに要素がある場合はクリアする
		for (int i = 0; i < kRankingNum; ++i)
		{
			int temp;
			file.read(reinterpret_cast<char*>(&temp), sizeof(int));
			m_ranking.push_back(temp);
		}
		file.close();
	}
}


/// <summary>
/// ファイル書き込み
/// </summary>
void ManagerResult::Save(int time)
{
	// クリアタイムがランキング内に入っている場合ランキングを更新する
	// 同じタイムの場合は更新しない
	auto it = std::find(m_ranking.begin(), m_ranking.end(), time);
	if (it != m_ranking.end())
	{
		// 同じタイムがある場合は更新しない
		return;
	}

	it = std::find_if(m_ranking.begin(), m_ranking.end(), [time](int t) { return t > time; });
	if (it != m_ranking.end())
	{
		m_ranking.insert(it, time);
		// 10位以上保存されないようにする
		if (m_ranking.size() > kRankingNum)
		{
			m_ranking.resize(kRankingNum);
		}
	}
	else
	{
		m_ranking.push_back(time);
	}

	// 順位を昇順にする
	std::sort(m_ranking.begin(), m_ranking.end(), [](int a, int b) { return a < b; });

	// クリアタイムを更新する
	m_clearTime = time;

	// ファイルに書き込む
	std::fstream file;
	file.open(fileName, std::ios::out | std::ios::binary);
	if (!file.is_open())	// ファイル読み込み失敗時
	{
#ifdef _DEBUG
		printfDx("ファイル書き込み失敗\n");
#endif
	}
	else	// ファイル読み込み成功
	{
		file.write(reinterpret_cast<char*>(&m_clearTime), sizeof(int));

		// ランキングの書き込み
		for (int i = 0; i < kRankingNum; ++i)
		{
			file.write(reinterpret_cast<char*>(&m_ranking[i]), sizeof(int));
		}
		file.close();
	}
}