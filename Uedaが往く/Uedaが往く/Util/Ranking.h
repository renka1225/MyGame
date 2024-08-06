#pragma once
#include <string>

/// <summary>
/// ランキング情報を更新する
/// </summary>
class Ranking
{
public:
	Ranking();
	~Ranking();
	void Update(const char* Domain, const char* URI);

private:
	std::string m_rank;
};

