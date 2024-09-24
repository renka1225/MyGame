#include "ManagerModel.h"
#include "DxLib.h"

ManagerModel::ManagerModel()
{
	m_playerHandle = MV1LoadModel("data/model/Duck.mv1");
	m_enemyHandle = MV1LoadModel("data/model/Shark.mv1");
}


ManagerModel::~ManagerModel()
{
	MV1DeleteModel(m_playerHandle);
	MV1DeleteModel(m_enemyHandle);
}
