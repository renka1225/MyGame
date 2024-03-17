#pragma once
#include "DxLib.h"
#include <memory>

class ManagerModel;
/// <summary>
/// 背景クラス
/// </summary>
class Background
{
public:
	Background(std::shared_ptr<ManagerModel> pModel);
	~Background();

	void Init();
	void Update();
	void Draw();
	void End();

private:
	// モデルクラスのポインタ
	std::shared_ptr<ManagerModel> m_pModel;

	// 表示位置
	VECTOR m_pos;

	// 水面の3Dモデル
	int m_waterHandle;
};

