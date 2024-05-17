#pragma once
#include "Rect.h"
#include "DxLib.h"
#include <memory>
#include <vector>

class ManagerModel;

/// <summary>
/// 敵クラス
/// </summary>
class Enemy
{
public:
	Enemy(std::shared_ptr<ManagerModel> pModel, VECTOR pos);
	virtual ~Enemy();
	void Init() {};
	void Update();
	void Draw();

	Rect GetColRect() const { return m_colRect; }	// 当たり判定を取得する
	
private:
	// モデルクラスのポインタ
	std::shared_ptr<ManagerModel> m_pModel;

	// 敵の位置
	VECTOR m_pos;
	// 当たり判定用の矩形
	Rect m_colRect;

	// 存在フラグ
	bool m_isExist;

	// 3Dモデル
	int m_modelHandle;

private:	// 定数

	static constexpr float kMove = -1.4f;						// 移動量
	static constexpr float kScale = 0.03f;						// 拡大率
	static constexpr int kWidth = 160;							// 敵の横幅
	static constexpr int kHeight = 50;							// 敵の縦幅
	static constexpr float kDirY = 180.0f * DX_PI_F / 180.0f;	// 向き
};