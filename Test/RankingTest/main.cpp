#include "DxLib.h"
#include <iostream>
#include<string>


/// <summary>
/// Http通信でのGet命令を送る事ができる命令
/// </summary>
/// <param name="domain">ドメイン名を入力</param>
/// <param name="uri">URIを入力</param>
/// <returns>string型で実行結果を得る(予定でまだやってません)</returns>
std::string HttpGet(const char* domain, const char* uri)
{
	/*適当な変数*/
	std::string ans;
	int i = 12;//文字の表示位置用

	/*文字関係*/
	unsigned int Cr = GetColor(255, 255, 255);	 // 白色の値を取得
	SetFontSize(12);                             //サイズ変更
	SetFontThickness(4);                         //太さを変更

	/*ネットワーク用の変数*/
	const int DATA_SIZE = 2560;		//8bitのでかい数(char最大要素数は268435455)
	char StrBuf[DATA_SIZE] = "";    // データバッファ
	IPDATA Ip;						// 接続用ＩＰアドレスデータ
	int NetHandle;					// ネットワークハンドル
	int DataLength;					// 受信データ量保存用変数

	/*Http通信を作成するための変数*/
	char HttpCmd[128] = "";

	//DxLibの余計な機能を切る。
	SetUseDXNetWorkProtocol(false);

	//DNSからドメイン名でIPアドレス取得
	int test = GetHostIPbyName(domain, &Ip);
	DrawFormatString(0, 0, 0xffffff, "GetDomain:%d", test);//0なら正常

	//取得したIPアドレスの確認
	DrawFormatString(0, 20, 0xffffff, "IpAdress;%d,%d,%d,%d", Ip.d1, Ip.d2, Ip.d3, Ip.d4);

	// 通信を確立
	NetHandle = ConnectNetWork(Ip, 80);
	DrawFormatString(0, 40, 0xffffff, "NetHandle:%d", NetHandle);

	// 確立が成功した場合のみ中の処理をする
	if (NetHandle != -1)
	{
		//Http命令の作成
		sprintf_s(HttpCmd, "GET %s HTTP/1.1\nHost: %s\n\n", uri, domain);
		DrawFormatString(0, 60, 0xffffff, "HttpCmd:\n%s", HttpCmd);

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
		NetWorkRecv(NetHandle, StrBuf, DATA_SIZE);    // データをバッファに取得

		// 受信したデータを描画
		DrawString(0, 120, StrBuf, 0xffffff);

		// キー入力待ち
		WaitKey();

		// 接続を断つ
		CloseNetWork(NetHandle);
	}

	return ans;
}

int m_time = 0;

/*Main*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//windowモード
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;
	}

	char KeyBuf[256];

	while (ProcessMessage() == 0)
	{
		// 画面のクリア
		ClearDrawScreen();

		// すべてのキーの状態を得る
		GetHitKeyStateAll(KeyBuf);

		if (KeyBuf[KEY_INPUT_Z] == 1)
		{
			break;
		}

		m_time++;
		m_time %= 1000;
		DrawFormatString(0, 150, 0x0000ff, "%d", m_time);
	}
	
	/*Http通信でGet命令を指定のアドレスに行っている*/
	// ランキングのデータベースを作成
	// MEMO:ゲーム開始時最初に1回だけ呼ぶ
	//std::string createRank = HttpGet("rueda.zombie.jp", "/Ranking/createRanking.php");
	// 画面クリア
	ClearDrawScreen();
	// ランキングの更新
	// 経過した時間を新たに追加する
	std::string uri = "/Ranking/updateRanking.php?clearTime=" + std::to_string(m_time);
	std::string updateRank = HttpGet("rueda.zombie.jp", uri.c_str());
	// 画面クリア
	ClearDrawScreen();
	//ランキングの取得
	std::string getRank = HttpGet("rueda.zombie.jp", "/Ranking/getRanking.php");


	WaitKey();// キー入力待ち
	DxLib_End();// ＤＸライブラリ使用の終了処理
	return 0;// ソフトの終了 
}