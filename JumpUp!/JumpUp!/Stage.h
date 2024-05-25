#pragma once

/// <summary>
/// ステージの描画等を行うクラス
/// </summary>
class Stage
{
public:
	Stage();
	~Stage();
	void Init();
	void Update();
	void Draw();

	// 平面のX方向の傾斜を取得
	VECTOR GetV3Vec1() const { return m_v3Vec1; }
	// 平面のY方向の傾斜を取得
	VECTOR GetV3Vec2() const { return m_v3Vec2; }

private:
	// 床の情報
	VECTOR m_floorPos;
	int m_floorHandle;	// 床の3Dモデル

	// 頂点データ
	VERTEX3D Vertex[4];
	WORD Index[6];

	// X方向の傾斜
	VECTOR m_v3Vec1;
	// Y方向の傾斜
	VECTOR m_v3Vec2;

	// 経過時間
	int m_time;
	// 表示画像
	int m_handle;

private:	// 定数
	// 床の拡大率
	static constexpr float kFloorScaleX = 50.0f;
	static constexpr float kFloorScaleY = 1.0f;
	static constexpr float kFloorScaleZ = 50.0f;
};

