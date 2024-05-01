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
	std::vector<int> m_ranking = {4000, 4200, 4400, 4600, 4800, 
								5000, 5200, 5400, 5600, 5800};
	// クリアタイム
	int m_clearTime;

private:
	const char* fileName = "saveData.bin";	//　ファイル名
	static constexpr int kRankingNum = 10;	// 保存する順位数
};