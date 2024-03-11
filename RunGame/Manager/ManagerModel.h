#pragma once

/// <summary>
/// 3Dモデルの管理クラス
/// </summary>
class ManagerModel
{
public:
	ManagerModel();
	virtual ~ManagerModel();

	int GetPlayerHandle() const{ return m_playerHandle; }
	int GetEnemyHandle() const{ return m_enemyHandle; }

private:
	int m_playerHandle;	// プレイヤー
	int m_enemyHandle;	// 敵
};