#pragma once
#include "Collidable.h"
#include <memory>

class Collidable;

/// <summary>
/// ステージの描画等を行うクラス
/// </summary>
class Stage : public Collidable
{
public:
	Stage();
	virtual ~Stage();
	void Init(std::shared_ptr<Physics> physics);
	void Final(std::shared_ptr<Physics> physics);
	void Update();
	void Draw();
	virtual void OnCollide()override;	// 衝突したとき

	// 平面のX方向の傾斜を取得
	VECTOR GetV3Vec1() const { return m_v3Vec1; }
	// 平面のY方向の傾斜を取得
	VECTOR GetV3Vec2() const { return m_v3Vec2; }

private:
	// 床の情報
	VECTOR m_floorPos;
	int m_floorHandle;	// 床のモデル

	// 頂点データ
	VERTEX3D Vertex[4];
	WORD Index[6];

	// X方向の傾斜
	VECTOR m_v3Vec1;
	// Y方向の傾斜
	VECTOR m_v3Vec2;

	// ステージの情報
	VECTOR m_stagePos;
	// ステージの3Dモデル
	int m_stageHandle;

private:	// 定数
	// 床の拡大率
	static constexpr float kFloorScaleX = 30.0f;
	static constexpr float kFloorScaleY = 10.0f;
	static constexpr float kFloorScaleZ = 20.0f;
};

