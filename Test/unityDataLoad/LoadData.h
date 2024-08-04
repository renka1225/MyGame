#pragma once
#include <string>
#include <vector>
#include <unordered_map>

/// <summary>
/// ファイルを読み込む
/// </summary>
class LoadData
{
public:
	LoadData();
	~LoadData();
	void Init();
	void Update();
	void Draw();

private:
	int m_handle; // 読み込むデータ
	std::unordered_map<std::string, int> m_model; // モデルデータ

	// 配置情報データ
	struct LocationData
	{
		std::string name;	// 名前
		std::string tag;	// タグ
		VECTOR pos;			// 座標
		VECTOR rot;			// 回転
		VECTOR scale;		// スケール
	};
	std::vector<LocationData> m_locationData;
};

