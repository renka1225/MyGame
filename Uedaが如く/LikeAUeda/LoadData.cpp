#include "DxLib.h"
#include "CharacterBase.h"
#include "LoadData.h"
#include <fstream>
#include <sstream>

// 定数
namespace
{
	const char* const kFileName = "data/data.csv";
}


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="data">キャラクター参照</param>
/// <param name="charType">キャラクターの種類</param>
LoadData::LoadData(CharacterBase& data, int charType)
{
	LoadCharaData(data, charType);
}


/// <summary>
/// デストラクタ
/// </summary>
LoadData::~LoadData()
{
}


/// <summary>
/// 描画
/// </summary>
void LoadData::Draw()
{
#ifdef _DEBUG
	// 読み込んだデータを表示する
	int y = 0;
	for (const auto& data : m_data)
	{
		DrawFormatString(0, 100+y, 0xffffff, "%f:", data);
		y += 20;
	}
#endif
}


/// <summary>
/// キャラクターのデータを読み込む
/// </summary>
/// <param name="data">キャラクター参照</param>
/// <param name="charCharType">キャラクターの種類</param>
void LoadData::LoadCharaData(CharacterBase& data, int charType)
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
		// getline(istringstream型の変数, 分割した文字列を格納する変数, ',で分割')
		while (getline(stream, field, ','))
		{
			try
			{
				// 文字列をfloatに変換してm_dataに追加する
				m_data.push_back(std::stof(field));
			}
			catch (const std::invalid_argument& e)
			{
				// 無効な文字列をスキップ
			}
		}
	}

	// プレイヤー
	if (charType == static_cast<int>(CharacterBase::CharaType::kPlayer))
	{
		data.m_status.maxHp = m_data[0];
		data.m_status.punchPower = m_data[1];
		data.m_status.kickPower = m_data[2];
		data.m_status.maxMoveSpeed = m_data[3];
	}
	// チュートリアル敵
	else if (charType == static_cast<int>(CharacterBase::CharaType::kEnemyTuto))
	{
		data.m_status.maxHp = m_data[4];
		data.m_status.punchPower = m_data[5];
		data.m_status.kickPower = m_data[6];
		data.m_status.maxMoveSpeed = m_data[7];
	}
}
