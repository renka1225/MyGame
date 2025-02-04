#pragma once

/// <summary>
/// フレーム数から秒、ミリ秒に変換する
/// </summary>
class ConversionTime
{
public:
	ConversionTime();
	~ConversionTime() {};
	void Change(int time);	// 秒、ミリ秒に変換

	int GetSec() const { return m_sec; }		// 秒取得
	int GetMilliSec() const { return m_milliSec; }	// ミリ秒取得

private:
	int m_sec;		// 秒
	int m_milliSec;	// ミリ秒
};

