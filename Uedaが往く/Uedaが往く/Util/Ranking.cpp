#include "DxLib.h"
#include "Vec2.h"
#include "Font.h"
#include "ConversionTime.h"
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
	constexpr int kMaxRankNum = 10;		// 表示するランキング数

	// ランキング表示
	const Vec2 kRankingPos = { 1000.0f, 400.0f };	// 表示位置
	constexpr float kRankingIntervalWidth= 300.0f;	// 横の表示間隔
	constexpr float kRankingIntervalHeight = 40.0f;	// 縦の表示間隔
	constexpr int kTextColor = 0xffffff;

}

/// <summary>
/// コンストラクタ
/// </summary>
Ranking::Ranking():
	m_pos(0),
	m_lineCount(0)
{
	m_rankingList.resize(kMaxRankNum);
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
	uri = kUpdateUri + std::to_string(clearTime);
	std::string getRank = HttpGet(kDomainName, uri.c_str());
}


/// <summary>
/// ランキング取得
/// </summary>
void Ranking::GetRanking()
{
	getRank = HttpGet(kDomainName, kGetUri);

	m_lineCount = 0;  // ランキングカウントをリセット
	size_t m_pos = 0;

	// 1位～10位まで取得する
	// MEMO:clearTimeだけを抽出する。clearTimeが見つからない場合はnposを返す
	while (m_lineCount < kMaxRankNum && (m_pos = getRank.find("\"clearTime\":")) != std::string::npos)
	{
		m_pos += strlen("\"clearTime\":");
		int clearTime = 0;
		int numChars = 0;

		if (sscanf_s(getRank.c_str() + m_pos, "%d%n", &clearTime, &numChars) == 1)
		{
			if (m_lineCount < kMaxRankNum)
			{
				m_rankingList[m_lineCount] = clearTime;  // ランキングリストに保存
				m_lineCount++;
			}

			// 次の要素に進む
			m_pos += numChars;				  // 読み取った文字数分だけ進める
			getRank = getRank.substr(m_pos);  // 残りの部分文字列を取得
		}
		else
		{
			break;  // sscanf_sが失敗した場合はループを終了
		}
	}
}


/// <summary>
/// ランキング描画
/// </summary>
void Ranking::DrawRanking()
{
	m_pos = getRank.find_first_of("\r\n");

	for (int i = 0; i < m_lineCount; i++)
	{
		// フレーム数から秒数に変換する
		int min = Conversion::ChangeMin(m_rankingList[i]);			 // 分
		int sec = Conversion::ChangeSec(m_rankingList[i]);			 // 秒
		int milliSec = Conversion::ChangeMilliSec(m_rankingList[i]); // ミリ秒

		std::string line = std::to_string(i + 1) + "位: " + std::to_string(min) + ":" + std::to_string(sec) + ":" + std::to_string(milliSec);

		// 1位～5位、6位～10位の表示位置をずらす
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
		//Http命令の作成
		sprintf_s(HttpCmd, "GET %s HTTP/1.1\nHost: %s\n\n", uri, domain);
#ifdef _DEBUG
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