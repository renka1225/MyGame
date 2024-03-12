#pragma once
#include "DxLib.h"
#include <memory>

class ManagerModel;

/// <summary>
/// 敵クラス
/// </summary>
class Enemy
{
public:
	Enemy(std::shared_ptr<ManagerModel> pModel);
	virtual ~Enemy();
	void Init();
	void Update();
	void Draw();
	void End();
	
private:
	// モデルクラスのポインタ
	std::shared_ptr<ManagerModel> m_pModel;

	// 表示位置
	VECTOR m_pos;
	// 移動量
	VECTOR m_move;

	// 3Dモデル
	int m_modelHandle;
};