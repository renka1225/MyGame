#pragma once

/// <summary>
/// �t���[��������b�A�~���b�ɕϊ�����
/// </summary>
class ConversionTime
{
public:
	ConversionTime();
	~ConversionTime() {};
	void Change(int time);	// �b�A�~���b�ɕϊ�

	int GetSec() const { return m_sec; }		// �b�擾
	int GetMilliSec() const { return m_milliSec; }	// �~���b�擾

private:
	int m_sec;		// �b
	int m_milliSec;	// �~���b
};

