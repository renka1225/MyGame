#pragma once
#include "DxLib.h"
#include <memory>
#include <vector>

class ConversionTime;

/// <summary>
/// クリアタイムの読み書き
/// </summary>
class ManagerResult
{
public:
	ManagerResult();
	~ManagerResult() {};
	void Load();	// ファイル読み込み
	void Save(int time);	// ファイル書き込み

	int GetClearTime() const { return m_clearTime; }			// クリアタイム取得
	std::vector<int> GetRanking() const { return m_ranking; }	// ランキング取得

private:
	std::shared_ptr<ConversionTime> m_pConversionTime;	// タイムに変換する

	// ランキング
	std::vector<int> m_ranking = {3600, 3660, 3690, 3720, 3750,
								3780, 3810, 3840, 3870, 3900};
	// クリアタイム
	int m_clearTime;

private:
	const char* fileName = "data/saveData.bin";	// 保存するファイル名
	static constexpr int kRankingNum = 10;	// 保存する順位数
};