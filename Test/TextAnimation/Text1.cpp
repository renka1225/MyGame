#include "DxLib.h"
#include "Text1.h"
#include <fstream>
#include <sstream>

// 定数
namespace
{
	const char* kFileName = "data/test.csv"; // ファイル名
	constexpr float kAmplitude = 8.0f;		 // 振れ幅
	constexpr float kCycle = 0.05f;			 // 周期
}

/// <summary>
/// コンストラクタ
/// </summary>
Text1::Text1():
	m_textPosY(0),
	m_time(0)
{
	LoadCsv();
}


/// <summary>
/// デストラクタ
/// </summary>
Text1::~Text1()
{
}


/// <summary>
/// 初期化
/// </summary>
void Text1::Init()
{
}


/// <summary>
/// 更新
/// </summary>
void Text1::Update()
{
	m_time++;
}


/// <summary>
/// 描画
/// </summary>
void Text1::Draw()
{
	int x = 0;

	for (const auto& line : m_text)
	{
		m_textPosY = kAmplitude * sin(m_time * kCycle - (x / 40.0f));
		DrawString(x, 20 + m_textPosY, line.c_str(), 0xffffff);
		x += 10;
	}
}


/// <summary>
/// CSVファイルからテキストを読み込む
/// </summary>
void Text1::LoadCsv()
{
	std::ifstream file(kFileName);
	m_text.clear();
	std::string line;

	// ファイルの入力取得
	// std::getline(読み取るファイルの変数, 入力文字列を格納する変数);
	while (std::getline(file, line))
	{
		std::istringstream stream(line);
		std::string field;

		// 文字列分割
		// getline(istringstream型の変数, 分割した文字列を格納する変数, ',で分割')
		while (getline(stream, field, ','))
		{
			for (char c : field)
			{
				std::string charStr(1, c);  // 1文字を文字列に変換
				m_text.push_back(charStr);  // 文字をベクターに追加
			}
		}
	}
}
