#pragma once
#include <string>

/// <summary>
/// �����L���O�����X�V����
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

