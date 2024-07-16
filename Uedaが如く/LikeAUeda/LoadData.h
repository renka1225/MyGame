#pragma once
#include <vector>

class CharacterBase;

/// <summary>
/// csvファイル読み込み
/// </summary>
class LoadData
{
public:
	LoadData() {};
	LoadData(CharacterBase& data, int charType);
	~LoadData();
	void Draw();

	// キャラクターのデータを読み込む
	void LoadCharaData(CharacterBase& data, int charType);

private:
	std::vector<float> m_data;
};