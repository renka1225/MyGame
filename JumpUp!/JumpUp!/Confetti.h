#pragma once
#include <vector>

/// <summary>
/// 紙吹雪を作成する
/// </summary>
namespace Confetti
{
	void CreateCofetti();	// 紙吹雪の作成
	void UpdateCofetti();	// 紙吹雪の更新
	void DrawCofetti();		// 紙吹雪の描画

	struct ConfettiInfo
	{
		int x;		// X座標
		int y;		// Y座標
		int size;	// サイズ
		int speed;	// 落下速度
		int color;	// 色
	};
	ConfettiInfo confettiInfo;

	extern std::vector<ConfettiInfo> confettis;
}
