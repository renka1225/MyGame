#pragma once
#include "Collidable.h"
#include <memory>

class Collidable;
class DrawDebug;

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
	void Draw(DrawDebug& drawDebug);
	virtual void OnCollide()override;	// 衝突したとき

	// 平面のX方向の傾斜を取得
	VECTOR GetV3Vec1() const { return m_v3Vec1; }
	// 平面のY方向の傾斜を取得
	VECTOR GetV3Vec2() const { return m_v3Vec2; }
	// ステージの位置を取得
	VECTOR GetStagePos() const { return m_stagePos; }
	// ステージモデルを取得
	int GetStageHandle() const { return m_stageHandle; }

private:
	// 床の情報
	VECTOR m_floorPos;	// 床の位置
	int m_floorHandle;	// 床のモデル

	// 頂点データ
	VERTEX3D Vertex[4];
	WORD Index[6];

	// X方向の傾斜
	VECTOR m_v3Vec1;
	// Y方向の傾斜
	VECTOR m_v3Vec2;

	// ステージの情報
	VECTOR m_stagePos;		// ステージの位置
	VECTOR m_stageScale;	// ステージの拡大率
	int m_stageHandle;		// ステージの3Dモデル

private:	// 定数
	// 床の拡大率
	static constexpr float kFloorScaleX = 30.0f;
	static constexpr float kFloorScaleY = 10.0f;
	static constexpr float kFloorScaleZ = 20.0f;

	// 当たり判定
	static constexpr float kCenterPosY = 5.0f;	// 地面の中心点を調整
};

