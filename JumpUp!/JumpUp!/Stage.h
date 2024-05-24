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

private:
	// 床の情報
	VECTOR m_floorPos;
	int m_floorHandle;	// 床の3Dモデル

private:	// 定数
	// 床の拡大率
	static constexpr float kFloorScaleX = 50.0f;
	static constexpr float kFloorScaleY = 1.0f;
	static constexpr float kFloorScaleZ = 50.0f;
};

