#include "DxLib.h"
#include "Ranking.h"

// 定数
namespace
{
	// ドメイン名
	const char* kDomainName = "rueda.zombie.jp";
	// URI
	const char* kCreateUri = "/Ranking/createRanking.php?clearTime=";  // 作成
	const char* kUpdateUri = "/Ranking/updateRanking.php?clearTime=";  // 更新
	const char* kGetUri = "/Ranking/getRanking.php";				   // 取得
	constexpr int kPortNum = 80;		// ポート番号
}

/// <summary>
/// コンストラクタ
/// </summary>
Ranking::Ranking()
{
	pos = 0;
}


/// <summary>
/// デストラクタ
/// </summary>
Ranking::~Ranking()
{
}


/// <summary>
/// ランキング作成
/// </summary>
void Ranking::CreateRanking()
{
	createRank = HttpGet(kDomainName, kCreateUri);
}


/// <summary>
/// ランキング更新
/// </summary>
/// <param name="clearTime">クリアタイム</param>
void Ranking::UpdateRanking(int clearTime)
{
	uri = "/Ranking/updateRanking.php?clearTime=" + std::to_string(clearTime);
	std::string getRank = HttpGet(kDomainName, uri.c_str());
}


/// <summary>
/// ランキング取得
/// </summary>
void Ranking::GetRanking()
{
	getRank = HttpGet(kDomainName, kGetUri);
}


/// <summary>
/// ランキング描画
/// </summary>
void Ranking::DrawRanking()
{
	// 1位～10位まで取得する
	// MEMO: std::string::nposは値が見つからなかった場合に値を返す
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
/// Http通信のGet命令を送る
/// </summary>
/// <param name="domain">ドメイン名</param>
/// <param name="uri">URI</param>
/// <returns>ランキングを取得</returns>
std::string Ranking::HttpGet(const char* domain, const char* uri)
{
	char HttpCmd[128] = ""; 	// Http通信を作成するための変数

	// DxLibの不要な機能をoffにする
	SetUseDXNetWorkProtocol(false);

	// DNSからドメイン名でIPアドレスを取得
	GetHostIPbyName(domain, &Ip);

	// 通信を確立
	NetHandle = ConnectNetWork(Ip, kPortNum);

	// 確立が成功した場合のみ中の処理をする
	if (NetHandle != -1)
	{
#ifdef _DEBUG
		//Http命令の作成
		sprintf_s(HttpCmd, "GET %s HTTP/1.1\nHost: %s\n\n", uri, domain);
		//DrawFormatString(0, 60, 0xffffff, "HttpCmd:\n%s", HttpCmd);
#endif // _DEBUG

		// データ送信(http命令を送る)
		NetWorkSend(NetHandle, HttpCmd, strlen(HttpCmd));

		// データがくるのを待つ
		while (!ProcessMessage())
		{
			// 取得していない受信データ量を得る
			DataLength = GetNetWorkDataLength(NetHandle);

			// 取得してない受信データ量が-1じゃない場合はループを抜ける
			if (DataLength != -1)
			{
				break;
			}
		}

		// データ受信
		NetWorkRecv(NetHandle, StrBuf, kDataSize);    // データをバッファに取得

		// 接続を断つ
		CloseNetWork(NetHandle);
	}


#ifdef _DEBUG
	//取得したIPアドレスの確認
	//DrawFormatString(0, 20, 0xffffff, "IpAdress;%d,%d,%d,%d", Ip.d1, Ip.d2, Ip.d3, Ip.d4);
	//DrawFormatString(0, 40, 0xffffff, "NetHandle:%d", NetHandle);
#endif // _DEBUG

	return StrBuf;
}