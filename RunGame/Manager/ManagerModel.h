#pragma once

/// <summary>
/// 3D���f���̊Ǘ��N���X
/// </summary>
class ManagerModel
{
public:
	ManagerModel();
	virtual ~ManagerModel();

	int GetPlayerHandle() const{ return m_playerHandle; }
	int GetEnemyHandle() const{ return m_enemyHandle; }
	int GetWaterHandle() const{ return m_waterHandle; }

private:
	int m_playerHandle;	// �v���C���[
	int m_enemyHandle;	// �G
	int m_waterHandle;	// ����
};