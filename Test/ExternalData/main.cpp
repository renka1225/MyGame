#include "DxLib.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

namespace
{
	const char* const kFileName = "data/data.csv";
}

std::vector<float> m_data;

/// <summary>
/// 外部データの読み込み
/// </summary>
void LoadData()
{
	std::ifstream file(kFileName);
	m_data.clear();
	std::string line;

	// ファイルの入力取得
	// std::getline(読み取るファイルの変数, 入力文字列を格納する変数);
	while (std::getline(file, line))
	{
		std::istringstream stream(line);
		std::string field;

		// 文字列分割
		// getline(istringstream型の変数, 分割した文字列を格納する変数, '何で分割するか')
		while (getline(stream, field, ','))
		{
			// 文字列をfloatに変換してm_dataに追加する
			try
			{
				m_data.push_back(std::stof(field));
			}
			catch (const std::invalid_argument& e)
			{
				// 無効な文字列をスキップ
			}
		}
	}
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;
	}

	// 外部データの読み込み
	LoadData();

	while (ProcessMessage() != -1)
	{
		// 読み込んだデータを表示する
		int y = 0;
		for (const auto& data : m_data)
		{
			DrawFormatString(0, y, 0xffffff, "%f:", data);
			y += 10;
		}

		// 画面が切り替わるのを待つ
		ScreenFlip();
	}

	DxLib_End();// ＤＸライブラリ使用の終了処理

	return 0;	// ソフトの終了 
}