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
	// ステージ1URI
	const char* kStage1CreateUri = "/Ranking/createRanking_stage1.php";				// 作成
	const char* kStage1UpdateUri = "/Ranking/updateRanking_stage1.php?clearTime=";  // 更新
	const char* kStage1GetUri = "/Ranking/getRanking_stage1.php";					// 取得
	// ステージ2URI
	const char* kStage2CreateUri = "/Ranking/createRanking_stage2.php";					// 作成
	const char* kStage2UpdateUri = "/Ranking/updateRanking_stage2.php?clearTime=";		// 更新
	const char* kStage2GetUri = "/Ranking/getRanking_stage2.php";						// 取得
	constexpr int kPortNum = 80;		// ポート番号
	constexpr int kMaxRankNum = 10;		// 表示するランキング数

	// ランキング表示
	constexpr float kRankingIntervalAdj = 28.0f;		// 表示位置調整
	constexpr int kTextColor = 0xffffff;				// テキストの色
	constexpr float kRankingIntervalWidth = 400.0f;		// 横の表示間隔
	// ステージ選択時
	const Vec2 kStageSlectRankPos = { 900, 320 };		// 表示位置
	constexpr float kStageSlectRankInterval = 60.0f;	// 縦の表示間隔
	// クリア時
	const Vec2 kRankingPos = { 1000.0f, 550.0f };		// 表示位置
	constexpr float kClearRankInterval = 80.0f;			// 縦の表示間隔

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
/// <param name="stageKind">ステージの種類</param>
void Ranking::CreateRanking(int stageKind)
{
	// ステージによってURIを変更する
	switch (stageKind)
	{
	case 1:
		createRank = HttpGet(kDomainName, kStage1CreateUri);
		break;
	case 2:
		createRank = HttpGet(kDomainName, kStage2CreateUri);
		break;
	}
}


/// <summary>
/// ランキング更新
/// </summary>
/// <param name="stageKind">ステージの種類</param>
/// <param name="clearTime">クリアタイム</param>
void Ranking::UpdateRanking(int stageKind, int clearTime)
{
	// ステージによってURIを変更する
	switch (stageKind)
	{
	case 1:
		uri = kStage1UpdateUri + std::to_string(clearTime);
		break;
	case 2:
		uri = kStage2UpdateUri + std::to_string(clearTime);
		break;
	}

	std::string getRank = HttpGet(kDomainName, uri.c_str());
}


/// <summary>
/// ランキング取得
/// </summary>
/// <param name="stageKind">ステージの種類</param>
void Ranking::GetRanking(int stageKind)
{
	// ステージによってURIを変更する
	switch (stageKind)
	{
	case 1:
		getRank = HttpGet(kDomainName, kStage1GetUri);
		break;
	case 2:
		getRank = HttpGet(kDomainName, kStage2GetUri);
		break;
	}

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
/// ステージ選択時ランキング表示
/// </summary>
void Ranking::DrawStageSelectRanking()
{
	m_pos = getRank.find_first_of("\r\n");

	for (int i = 0; i < m_lineCount; i++)
	{
		// フレーム数から秒数に変換する
		int min = Conversion::ChangeMin(m_rankingList[i]);			 // 分
		int sec = Conversion::ChangeSec(m_rankingList[i]);			 // 秒
		int milliSec = Conversion::ChangeMilliSec(m_rankingList[i]); // ミリ秒

		// 1位～5位、6位～10位の表示位置をずらす
		if (i < 5)
		{
			DrawFormatStringFToHandle(kStageSlectRankPos.x, kStageSlectRankPos.y + i * kStageSlectRankInterval,
				kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kRanking)], "%d位 %02d:%02d:%03d", (i + 1), min, sec, milliSec);
		}
		else if (i < 9)
		{
			DrawFormatStringFToHandle(kStageSlectRankPos.x + kRankingIntervalWidth, kStageSlectRankPos.y + (i - 5) * kStageSlectRankInterval,
				kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kRanking)], "%d位 %02d:%02d:%03d", (i + 1), min, sec, milliSec);
		}
		else
		{
			DrawFormatStringFToHandle(kStageSlectRankPos.x + kRankingIntervalWidth - kRankingIntervalAdj, kStageSlectRankPos.y + (i - 5) * kStageSlectRankInterval,
				kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kRanking)], "%d位 %02d:%02d:%03d", (i + 1), min, sec, milliSec);
		}
	}
}


/// <summary>
/// クリア時のランキング描画
/// </summary>
void Ranking::DrawClearRanking()
{
	m_pos = getRank.find_first_of("\r\n");

	for (int i = 0; i < m_lineCount; i++)
	{
		// フレーム数から秒数に変換する
		int min = Conversion::ChangeMin(m_rankingList[i]);			 // 分
		int sec = Conversion::ChangeSec(m_rankingList[i]);			 // 秒
		int milliSec = Conversion::ChangeMilliSec(m_rankingList[i]); // ミリ秒

		// 1位～5位、6位～10位の表示位置をずらす
		if (i < 5)
		{
			DrawFormatStringFToHandle(kRankingPos.x, kRankingPos.y + i * kClearRankInterval,
				kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kRanking)], "%d位 %02d:%02d:%03d", (i + 1), min, sec, milliSec);
		}
		else if(i < 9)
		{
			DrawFormatStringFToHandle(kRankingPos.x + kRankingIntervalWidth, kRankingPos.y + (i - 5) * kClearRankInterval,
				kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kRanking)], "%d位 %02d:%02d:%03d", (i + 1), min, sec, milliSec);
		}
		else
		{ 
			DrawFormatStringFToHandle(kRankingPos.x + kRankingIntervalWidth - kRankingIntervalAdj, kRankingPos.y + (i - 5) * kClearRankInterval,
				kTextColor, Font::m_fontHandle[static_cast<int>(Font::FontId::kRanking)], "%d位 %02d:%02d:%03d", (i + 1), min, sec, milliSec);
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
		NetWorkSend(NetHandle, HttpCmd, static_cast<int>(strlen(HttpCmd)));

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