#pragma once
#include <vector>

/// <summary>
/// 紙吹雪を作成する
/// </summary>
namespace Confetti
{
	void CreateCofetti();	// 作成
	void DeleteCofetti();	// 削除
	void UpdateCofetti();	// 更新
	void DrawCofetti();		// 描画

	struct ConfettiInfo
	{
		int x;		// X座標
		int y;		// Y座標
		int size;	// サイズ
		int speed;	// 落下速度
		int color;	// 色
	};

	extern std::vector<ConfettiInfo> confettis;
}
