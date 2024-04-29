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
	void CreateGroundModel();	// �n�ʂ̐���
	void CreateTreeModel();		// �؂̐���

	int GetPlayerModel() const { return m_playerModel; }
	int GetGroundModel() const { return m_groundModel; }
	int GetTreeModel() const { return m_treeModel; }

private:
	std::vector<std::shared_ptr<ModelBase>> m_pGroundModel;	// �n�ʂ̃��f��
	std::vector<std::shared_ptr<ModelBase>> m_pTreeModel;	// �؂̃��f��

	int m_playerModel;	// �v���C���[��3D���f��
	int m_groundModel;	// �n�ʂ�3D���f��
	int m_desertModel;	// �n�ʂ�3D���f��
	int m_treeModel;	// �؂�3D���f��

private:
	static constexpr int kGroundNum = 3;			// �ݒu����n�ʂ̐�
	static constexpr float kGroundPosX = 150.0f;	// �ݒu����n�ʂ̈ʒuX
	static constexpr float kGroundPosY = 100.0f;	// �ݒu����n�ʂ̈ʒuY
	static constexpr float kGroundPosZ = 0.0f;		// �ݒu����n�ʂ̈ʒuZ
	static constexpr int kTreeNum = 10;				// ���v�̖؂̐�
	static constexpr int kTreeColNum = 5;			// 1��ɐݒu����؂̐�
	static constexpr float kTreePosX = 100.0f;		// �ݒu����؂̈ʒuX
	static constexpr float kTreePosY = -50.0f;		// �ݒu����؂̈ʒuY
	static constexpr float kTreePosZ = -70.0f;		// �ݒu����؂̈ʒuZ
	static constexpr float kTreeInitPosZ =100.0f;	// �ݒu����؂̏����ʒuZ
};

