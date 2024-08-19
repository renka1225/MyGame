#include "DxLib.h"
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
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
Ranking::Ranking()
{
	pos = 0;
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
	uri = "/Ranking/updateRanking.php?clearTime=" + std::to_string(clearTime);
	std::string getRank = HttpGet(kDomainName, uri.c_str());
}


/// <summary>
/// �����L���O�擾
/// </summary>
void Ranking::GetRanking()
{
	getRank = HttpGet(kDomainName, kGetUri);
}


/// <summary>
/// �����L���O�`��
/// </summary>
void Ranking::DrawRanking()
{
	// 1�ʁ`10�ʂ܂Ŏ擾����
	// MEMO: std::string::npos�͒l��������Ȃ������ꍇ�ɒl��Ԃ�
	pos = getRank.find("\r\n");
	if (pos != std::string::npos)
	{
		std::string line = getRank.substr(0, pos + 256);

		if (!line.empty())
		{
			DrawString(0, 0, line.c_str(), 0xffffff);
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
#ifdef _DEBUG
		//Http���߂̍쐬
		sprintf_s(HttpCmd, "GET %s HTTP/1.1\nHost: %s\n\n", uri, domain);
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