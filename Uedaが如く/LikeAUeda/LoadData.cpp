#include "DxLib.h"
#include "CharacterBase.h"
#include "LoadData.h"
#include <fstream>
#include <sstream>

// 定数
namespace
{
	const char* const kCharStatusFileName = "data/csv/charStatus.csv";	// キャラクターデータのファイル名
	const char* const kAnimSpeedFileName = "data/csv/animSpeed.csv";	// アニメーション速度データのファイル名

	constexpr int kAnimNum = 14;	// 1キャラクターのアニメーションの数
}


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="data">キャラクター参照</param>
/// <param name="charType">キャラクターの種類</param>
LoadData::LoadData(CharacterBase& data, int charType)
{
	LoadCharaData(data, charType);
	LoadAnimSpeedData(data, charType);
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
	for (const auto& data : m_charData)
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
	std::ifstream file(kCharStatusFileName);
	m_charData.clear();
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
				m_charData.push_back(std::stof(field));
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
		data.m_status.maxHp = m_charData[0];
		data.m_status.punchPower = m_charData[1];
		data.m_status.kickPower = m_charData[2];
		data.m_status.maxMoveSpeed = m_charData[3];
	}
	// チュートリアル敵
	else if (charType == static_cast<int>(CharacterBase::CharaType::kEnemyTuto))
	{
		data.m_status.maxHp = m_charData[4];
		data.m_status.punchPower = m_charData[5];
		data.m_status.kickPower = m_charData[6];
		data.m_status.maxMoveSpeed = m_charData[7];
	}
}


/// <summary>
/// アニメーション速度のデータを読み込む
/// </summary>
/// <param name="data">キャラクター参照</param>
/// <param name="charType">キャラクターの種類</param>
void LoadData::LoadAnimSpeedData(CharacterBase& data, int charType)
{
	std::ifstream file(kAnimSpeedFileName);
	m_animSpeedData.clear();
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
				m_animSpeedData.push_back(std::stof(field));
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
		data.m_animSpeed.none = m_animSpeedData[0 + charType * kAnimNum];
		data.m_animSpeed.avoid = m_animSpeedData[1 + charType * kAnimNum];
		data.m_animSpeed.down = m_animSpeedData[2 + charType * kAnimNum];
		data.m_animSpeed.fightIdle = m_animSpeedData[3 + charType * kAnimNum];
		data.m_animSpeed.gettingUp = m_animSpeedData[4 + charType * kAnimNum];
		data.m_animSpeed.grab = m_animSpeedData[5 + charType * kAnimNum];
		data.m_animSpeed.guard = m_animSpeedData[6 + charType * kAnimNum];
		data.m_animSpeed.kick = m_animSpeedData[7 + charType * kAnimNum];
		data.m_animSpeed.punch = m_animSpeedData[8 + charType * kAnimNum];
		data.m_animSpeed.comboPunch = m_animSpeedData[9 + charType * kAnimNum];
		data.m_animSpeed.receive = m_animSpeedData[10 + charType * kAnimNum];
		data.m_animSpeed.run = m_animSpeedData[11 + charType * kAnimNum];
		data.m_animSpeed.stand = m_animSpeedData[12 + charType * kAnimNum];
		data.m_animSpeed.Stumble = m_animSpeedData[13 + charType * kAnimNum];
	}
	// チュートリアル敵
	else if (charType == static_cast<int>(CharacterBase::CharaType::kEnemyTuto))
	{
		data.m_animSpeed.none = m_animSpeedData[0 + charType * kAnimNum];
		data.m_animSpeed.avoid = m_animSpeedData[1 + charType * kAnimNum];
		data.m_animSpeed.down = m_animSpeedData[2 + charType * kAnimNum];
		data.m_animSpeed.fightIdle = m_animSpeedData[3 + charType * kAnimNum];
		data.m_animSpeed.gettingUp = m_animSpeedData[4 + charType * kAnimNum];
		data.m_animSpeed.grab = m_animSpeedData[5 + charType * kAnimNum];
		data.m_animSpeed.guard = m_animSpeedData[6 + charType * kAnimNum];
		data.m_animSpeed.kick = m_animSpeedData[7 + charType * kAnimNum];
		data.m_animSpeed.punch = m_animSpeedData[8 + charType * kAnimNum];
		data.m_animSpeed.comboPunch = m_animSpeedData[9 + charType * kAnimNum];
		data.m_animSpeed.receive = m_animSpeedData[10 + charType * kAnimNum];
		data.m_animSpeed.run = m_animSpeedData[11 + charType * kAnimNum];
		data.m_animSpeed.stand = m_animSpeedData[12 + charType * kAnimNum];
		data.m_animSpeed.Stumble = m_animSpeedData[13 + charType * kAnimNum];
	}
}
