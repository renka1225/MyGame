#pragma once

class DrawDebug;

/// <summary>
/// ステージの更新と描画を行うクラス
/// </summary>
class Stage
{
public:
	Stage();
	virtual ~Stage();
	void Init();
	void Update();
	void Draw(DrawDebug& drawDebug);

	// 平面のX方向の傾斜を取得
	VECTOR GetV3Vec1() const { return m_v3Vec1; }
	// 平面のY方向の傾斜を取得
	VECTOR GetV3Vec2() const { return m_v3Vec2; }
	// ステージの位置を取得
	VECTOR GetStagePos() const { return m_stagePos; }
	// ステージモデルを取得
	int GetStageHandle() const { return m_stageHandle; }

private:
	void CreateFloor();	// 床を作成する

private:
	// 床の情報
	VECTOR m_floorPos;	// 床の位置
	int m_floorHandle;	// 床のモデル
	VECTOR m_v3Vec1;	// X方向の傾斜
	VECTOR m_v3Vec2;	// Y方向の傾斜
	// 頂点データ
	VERTEX3D m_vertex[4];
	WORD m_index[6];

	// ステージの情報
	// TODO: 後ほど複数にするのでvectorにする
	VECTOR m_stagePos;		// ステージの位置
	VECTOR m_stageScale;	// ステージの拡大率
	float m_angle;			// ステージの角度
	int m_stageHandle;		// ステージの3Dモデル
};

