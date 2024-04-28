#pragma once
#include <vector>
#include <memory>

class ModelBase;

/// <summary>
/// 3D���f���Ǘ��N���X
/// </summary>
class ManagerModel
{
public:
	ManagerModel();
	~ManagerModel();
	void Update();
	void Draw();
	void GreateTreeModel();	// �؂̐���

	int GetPlayerModel() const { return m_playerModel; }
	int GetGroundModel() const { return m_groundModel; }
	int GetTreeModel() const { return m_treeModel; }

private:
	std::vector<std::shared_ptr<ModelBase>> m_model;

	int m_playerModel;	// �v���C���[��3D���f��
	int m_groundModel;	// �n�ʂ�3D���f��
	int m_treeModel;	// �؂�3D���f��

private:
	static constexpr int kTreeNum = 10;	// �ݒu����؂̐�
};

