#include "DrawDebug.h"
#include "ConversionTime.h"

/// <summary>
/// グリッド表示
/// </summary>
void DrawDebug::DrawGrid()
{
	for (int x = -50; x <= 50; x += 10)
	{
		DrawLine3D(VGet(static_cast<float>(x), 0, -50), VGet(static_cast<float>(x), 0, 50), 0xffff00);
	}
	for (int z = -50; z <= 50; z += 10)
	{
		DrawLine3D(VGet(-50, 0, static_cast<float>(z)), VGet(50, 0, static_cast<float>(z)), 0xff0000);
	}

	// X+-,Z+-の方向が分かりやすいように表示を追加する
	VECTOR dispPos = ConvWorldPosToScreenPos(VGet(50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(-50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X-", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, 50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, -50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z-", 0xffffff);
	}
}


/// <summary>
/// プレイヤーの情報を描画
/// </summary>
/// <param name="pos">プレイヤーの座標</param>
///  <param name="state">現在のプレイヤーの状態</param>
void DrawDebug::DrawPlayerInfo(VECTOR pos, Player::State state)
{
	DrawFormatString(0, 40, 0xffffff, "Player座標(x:%f, y:%f, z:%f)", pos.x, pos.y, pos.z);

	// 現在の状態を描画
	if (state == Player::State::kStand)
	{
		DrawString(0, 60, "待機中", 0xffffff);
	}
	if (state == Player::State::kRun)
	{
		DrawString(0, 60, "移動中", 0xffffff);
	}
	if (state == Player::State::kJump)
	{
		DrawString(0, 60, "ジャンプ中", 0xffffff);
	}
	if (state == Player::State::kFall)
	{
		DrawString(0, 60, "落下中", 0xffffff);
	}
}


/// <summary>
/// カメラの情報を描画
/// </summary>
/// <param name="pos">カメラ座標</param>
/// <param name="target">カメラの注視点座標</param>
void DrawDebug::DrawCameraInfo(VECTOR pos, VECTOR target)
{
	DrawFormatString(0, 60, 0xffffff, "カメラ座標(x:%f, y:%f, z:%f)", pos.x, pos.y, pos.z);
	DrawFormatString(0, 80, 0xffffff, "注視点座標(x:%f, y:%f, z:%f)", target.x, target.y, target.z);
}


/// <summary>
/// タイムを表示する
/// </summary>
/// <param name="time">経過時間</param>
void DrawDebug::DrawTime(int frame)
{
	DrawFormatString(0, 80, 0xffffff, "タイム:%02d:%02d:%03d", 
		Conversion::ChangeMin(frame), Conversion::ChangeSec(frame), Conversion::ChangeMilliSec(frame));
}
