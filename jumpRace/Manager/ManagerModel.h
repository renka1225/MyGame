#pragma once
#include <vector>
#include <memory>

class ModelBase;

/// <summary>
/// 3Dモデル管理クラス
/// </summary>
class ManagerModel
{
public:
	ManagerModel();
	~ManagerModel();
	void Update();
	void Draw();
	void CreateGroundModel();	// 地面の生成
	void CreateTreeModel();		// 木の生成

	int GetPlayerModel() const { return m_playerModel; }

private:
	std::vector<std::shared_ptr<ModelBase>> m_pGroundModel;	// 地面のモデル
	std::vector<std::shared_ptr<ModelBase>> m_pTreeModel;	// 木のモデル

	int m_playerModel;	// プレイヤーの3Dモデル
	int m_groundModel;	// 地面の3Dモデル
	int m_desertModel;	// 地面の3Dモデル
	int m_treeModel;	// 木の3Dモデル

private:
	static constexpr int kGroundNum = 3;				// 設置する地面の数
	static constexpr float kGroundPosX = 450.0f;		// 設置する地面の位置X
	static constexpr float kGroundPosY = -100.0f;		// 設置する地面の位置Y
	static constexpr float kDesertGroundPosY = -110.0f;	// 横の地面の位置Y
	static constexpr float kGroundPosZ = 0.0f;			// 設置する地面の位置Z
	static constexpr int kTreeNum = 10;					// 合計の木の数
	static constexpr int kTreeColNum = 5;				// 1列に設置する木の数
	static constexpr float kTreePosX = 150.0f;			// 設置する木の位置X
	static constexpr float kTreePosY = -50.0f;			// 設置する木の位置Y
	static constexpr float kTreePosZ = -70.0f;			// 設置する木の位置Z
	static constexpr float kTreeInitPosZ = 100.0f;		// 設置する木の初期位置Z
};

