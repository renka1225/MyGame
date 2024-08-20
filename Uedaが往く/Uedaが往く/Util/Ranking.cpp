#include "DxLib.h"
#include "Vec2.h"
#include "Font.h"
#include "ConversionTime.h"
#include "Ranking.h"

// �萔
namespace
{
	// �h���C����
	const char* kDomainName = "rueda.zombie.jp";
	// URI
	const char* kCreateUri = "/Ranking/createRanking.php?clearTime=";  // �쐬
	const char* kUpdateUri = "/Ranking/updateRanking.php?clearTime=";  // �X�V
	const char* kGetUri = "/Ranking/getRanking.php";				   // �擾
	constexpr int kPortNum = 80;		// �|�[�g�ԍ�
	constexpr int kMaxRankNum = 10;		// �\�����郉���L���O��

	// �����L���O�\��
	const Vec2 kRankingPos = { 1000.0f, 400.0f };	// �\���ʒu
	constexpr float kRankingIntervalWidth= 300.0f;	// ���̕\���Ԋu
	constexpr float kRankingIntervalHeight = 40.0f;	// �c�̕\���Ԋu
	constexpr int kTextColor = 0xffffff;

}

/// <summary>
/// �R���X�g���N�^
/// </summary>
Ranking::Ranking():
	m_pos(0),
	m_lineCount(0)
{
	m_rankingList.resize(kMaxRankNum);
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
Ranking::~Ranking()
{
}


/// <summary>
/// �����L���O�쐬
/// </summary>
void Ranking::CreateRanking()
{
	createRank = HttpGet(kDomainName, kCreateUri);
}


/// <summary>
/// �����L���O�X�V
/// </summary>
/// <param name="clearTime">�N���A�^�C��</param>
void Ranking::UpdateRanking(int clearTime)
{
	uri = kUpdateUri + std::to_string(clearTime);
	std::string getRank = HttpGet(kDomainName, uri.c_str());
}


/// <summary>
/// �����L���O�擾
/// </summary>
void Ranking::GetRanking()
{
	getRank = HttpGet(kDomainName, kGetUri);

	m_lineCount = 0;  // �����L���O�J�E���g�����Z�b�g
	size_t m_pos = 0;

	// 1�ʁ`10�ʂ܂Ŏ擾����
	// MEMO:clearTime�����𒊏o����BclearTime��������Ȃ��ꍇ��npos��Ԃ�
	while (m_lineCount < kMaxRankNum && (m_pos = getRank.find("\"clearTime\":")) != std::string::npos)
	{
		m_pos += strlen("\"clearTime\":");
		int clearTime = 0;
		int numChars = 0;

		if (sscanf_s(getRank.c_str() + m_pos, "%d%n", &clearTime, &numChars) == 1)
		{
			if (m_lineCount < kMaxRankNum)
			{
				m_rankingList[m_lineCount] = clearTime;  // �����L���O���X�g�ɕۑ�
				m_lineCount++;
			}

			// ���̗v�f�ɐi��
			m_pos += numChars;				  // �ǂݎ�����������������i�߂�
			getRank = getRank.substr(m_pos);  // �c��̕�����������擾
		}
		else
		{
			break;  // sscanf_s�����s�����ꍇ�̓��[�v���I��
		}
	}
}


/// <summary>
/// �����L���O�`��
/// </summary>
void Ranking::DrawRanking()
{
	m_pos = getRank.find_first_of("\r\n");

	for (int i = 0; i < m_lineCount; i++)
	{
		// �t���[��������b���ɕϊ�����
		int min = Conversion::ChangeMin(m_rankingList[i]);			 // ��
		int sec = Conversion::ChangeSec(m_rankingList[i]);			 // �b
		int milliSec = Conversion::ChangeMilliSec(m_rankingList[i]); // �~���b

		std::string line = std::to_string(i + 1) + "��: " + std::to_string(min) + ":" + std::to_string(sec) + ":" + std::to_string(milliSec);

		// 1�ʁ`5�ʁA6�ʁ`10�ʂ̕\���ʒu�����炷
		if (i < 5)
		{
			DrawStringFToHandle(kRankingPos.x, kRankingPos.y + i * kRankingIntervalHeight, 
				line.c_str(), kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kRanking)]);
		}
		else
		{
			DrawStringFToHandle(kRankingPos.x + kRankingIntervalWidth, kRankingPos.y + (i - 5) * kRankingIntervalHeight,
				line.c_str(), kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kRanking)]);
		}
	}
}


/// <summary>
/// Http�ʐM��Get���߂𑗂�
/// </summary>
/// <param name="domain">�h���C����</param>
/// <param name="uri">URI</param>
/// <returns>�����L���O���擾</returns>
std::string Ranking::HttpGet(const char* domain, const char* uri)
{
	char HttpCmd[128] = ""; 	// Http�ʐM���쐬���邽�߂̕ϐ�

	// DxLib�̕s�v�ȋ@�\��off�ɂ���
	SetUseDXNetWorkProtocol(false);

	// DNS����h���C������IP�A�h���X���擾
	GetHostIPbyName(domain, &Ip);

	// �ʐM���m��
	NetHandle = ConnectNetWork(Ip, kPortNum);

	// �m�������������ꍇ�̂ݒ��̏���������
	if (NetHandle != -1)
	{
		//Http���߂̍쐬
		sprintf_s(HttpCmd, "GET %s HTTP/1.1\nHost: %s\n\n", uri, domain);
#ifdef _DEBUG
		//DrawFormatString(0, 60, 0xffffff, "HttpCmd:\n%s", HttpCmd);
#endif // _DEBUG

		// �f�[�^���M(http���߂𑗂�)
		NetWorkSend(NetHandle, HttpCmd, strlen(HttpCmd));

		// �f�[�^������̂�҂�
		while (!ProcessMessage())
		{
			// �擾���Ă��Ȃ���M�f�[�^�ʂ𓾂�
			DataLength = GetNetWorkDataLength(NetHandle);

			// �擾���ĂȂ���M�f�[�^�ʂ�-1����Ȃ��ꍇ�̓��[�v�𔲂���
			if (DataLength != -1)
			{
				break;
			}
		}

		// �f�[�^��M
		NetWorkRecv(NetHandle, StrBuf, kDataSize);    // �f�[�^���o�b�t�@�Ɏ擾

		// �ڑ���f��
		CloseNetWork(NetHandle);
	}


#ifdef _DEBUG
	//�擾����IP�A�h���X�̊m�F
	//DrawFormatString(0, 20, 0xffffff, "IpAdress;%d,%d,%d,%d", Ip.d1, Ip.d2, Ip.d3, Ip.d4);
	//DrawFormatString(0, 40, 0xffffff, "NetHandle:%d", NetHandle);
#endif // _DEBUG

	return StrBuf;
}