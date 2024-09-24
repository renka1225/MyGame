#pragma once

/// <summary>
/// ƒtƒŒ[ƒ€”‚©‚ç•bAƒ~ƒŠ•b‚É•ÏŠ·‚·‚é
/// </summary>
class ConversionTime
{
public:
	ConversionTime();
	~ConversionTime() {};
	void Change(int time);	// •bAƒ~ƒŠ•b‚É•ÏŠ·

	int GetSec() const { return m_sec; }		// •bæ“¾
	int GetMilliSec() const { return m_milliSec; }	// ƒ~ƒŠ•bæ“¾

private:
	int m_sec;		// •b
	int m_milliSec;	// ƒ~ƒŠ•b
};

