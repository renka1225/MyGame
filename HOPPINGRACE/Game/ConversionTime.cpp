#include "ConversionTime.h"

/// <summary>
/// コンストラクタ
/// </summary>
ConversionTime::ConversionTime() :
	m_sec(0),
	m_milliSec(0)
{
}

void ConversionTime::Change(int time)
{
	m_milliSec = time * 1000 / 60;
	m_sec = m_milliSec / 1000;
	m_milliSec %= 1000;
}
