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
	void GreateTreeModel();	// 木の生成

	int GetPlayerModel() const { return m_playerModel; }
	int GetGroundModel() const { return m_groundModel; }
	int GetTreeModel() const { return m_treeModel; }

private:
	std::vector<std::shared_ptr<ModelBase>> m_model;

	int m_playerModel;	// プレイヤーの3Dモデル
	int m_groundModel;	// 地面の3Dモデル
	int m_treeModel;	// 木の3Dモデル

private:
	static constexpr int kTreeNum = 10;	// 設置する木の数
};

