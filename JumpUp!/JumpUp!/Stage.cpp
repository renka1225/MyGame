#include "DxLib.h"
#include "Stage.h"

/// <summary>
/// コンストラクタ
/// </summary>
Stage::Stage():
	m_floorPos(VGet(0.0f, 0.0f, 0.0f))
{
	m_floorHandle = MV1LoadModel("data/model/floor.mv1");
}

/// <summary>
/// デストラクタ
/// </summary>
Stage::~Stage()
{
	MV1DeleteModel(m_floorHandle);
}

/// <summary>
/// 初期化
/// </summary>
void Stage::Init()
{
	MV1SetPosition(m_floorHandle, VGet(0.0f, 0.0f, 0.0f));
	MV1SetScale(m_floorHandle, VGet(kFloorScaleX, kFloorScaleY, kFloorScaleZ));
}

/// <summary>
/// 更新
/// </summary>
void Stage::Update()
{
}

/// <summary>
/// 描画
/// </summary>
void Stage::Draw()
{
	// 床を描画する
	MV1DrawModel(m_floorHandle);
}
