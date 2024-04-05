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
	Background();
	~Background() {};

	void Init();
	void Update();
	void Draw();
	void End();

private:
	// モデルクラスのポインタ
	std::shared_ptr<ManagerModel> m_pModel;

	// 表示位置
	VECTOR m_pos;
	VECTOR m_pos2;

	// 背景
	int m_background;
	int m_background2;

private:	// 定数
	static constexpr float kBgSize = 300.0f;	// 背景画像のサイズ
	static constexpr float kBgMove = -0.005f;	// 背景の移動量
};

