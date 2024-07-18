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
	const char* const kColFileName = "data/csv/collision.csv";			// 当たり判定データのファイル名

	constexpr int kStatusNum = 4;	// 1キャラクターのステータス数
	constexpr int kAnimNum = 14;	// 1キャラクターのアニメーションの数
	constexpr int kColNum = 16;		// 1キャラクターの当たり判定の情報数
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
	LoadColData(data, charType);
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

	// 値を代入する
	data.m_status.maxHp = m_charData[0 + charType * kStatusNum];
	data.m_status.punchPower = m_charData[1 + charType * kStatusNum];
	data.m_status.kickPower = m_charData[2 + charType * kStatusNum];
	data.m_status.maxMoveSpeed = m_charData[3 + charType * kStatusNum];
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

	// 値を代入する
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


/// <summary>
/// 当たり判定情報を読み込む
/// </summary>
/// <param name="data"></param>
/// <param name="charType"></param>
void LoadData::LoadColData(CharacterBase& data, int charType)
{
	std::ifstream file(kColFileName);
	m_colData.clear();
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
				m_colData.push_back(std::stof(field));
			}
			catch (const std::invalid_argument& e)
			{
				// 無効な文字列をスキップ
			}
		}
	}

	// 値を代入する
	data.m_colInfo.bodyHeight = m_colData[0 + charType * kColNum];
	data.m_colInfo.bodyRadius = m_colData[1 + charType * kColNum];
	data.m_colInfo.aimRadius = m_colData[2 + charType * kColNum];
	data.m_colInfo.legRadius = m_colData[3 + charType * kColNum];
	data.m_colInfo.armStartPos.x = m_colData[4 + charType * kColNum];
	data.m_colInfo.armStartPos.y = m_colData[5 + charType * kColNum];
	data.m_colInfo.armStartPos.z = m_colData[6 + charType * kColNum];
	data.m_colInfo.armEndPos.x = m_colData[7 + charType * kColNum];
	data.m_colInfo.armEndPos.y = m_colData[8 + charType * kColNum];
	data.m_colInfo.armEndPos.z = m_colData[9 + charType * kColNum];
	data.m_colInfo.legStartPos.x = m_colData[10 + charType * kColNum];
	data.m_colInfo.legStartPos.y = m_colData[11 + charType * kColNum];
	data.m_colInfo.legStartPos.z = m_colData[12 + charType * kColNum];
	data.m_colInfo.legEndPos.x = m_colData[13 + charType * kColNum];
	data.m_colInfo.legEndPos.y = m_colData[14 + charType * kColNum];
	data.m_colInfo.legEndPos.z = m_colData[15 + charType * kColNum];
}
