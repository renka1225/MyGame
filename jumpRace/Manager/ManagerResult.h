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
	std::vector<int> m_ranking = {4002, 4205, 4410, 4614, 4810, 
								5010, 5210, 5410, 5610, 5810};
	// クリアタイム
	int m_clearTime;

private:
	const char* fileName = "data/saveData.bin";	// 保存するファイル名
	static constexpr int kRankingNum = 10;	// 保存する順位数
};