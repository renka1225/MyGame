#pragma once
#include "DxLib.h"
#include <memory>

class ManagerModel;

/// <summary>
/// 背景クラス
/// </summary>
class Background
{
public:
	Background();
	~Background();

	void Init() {};
	void Update() {};
	void Draw();

private:
	// 表示位置
	VECTOR m_pos;
	VECTOR m_pos2;
	VECTOR m_pos3;

	// 背景
	int m_background;
	int m_background2;
	int m_background3;
	int m_bg;

	// 画像サイズ
	struct Size
	{
		int width;
		int height;
	};

private:	// 定数
	static constexpr float kBgScale = 1.2f;			// 背景画像のサイズ
	static constexpr float kBg2Scale = 1.0f;		// 背景画像のサイズ
	static constexpr float kBg3Scale = 0.9f;		// 背景画像のサイズ
	static constexpr float kBgMove = -0.1f;			// 背景の移動量

	// 背景の描画位置
	static constexpr float kBgPosX = 50.0f;			// 最背面のX座標
	static constexpr float kBg2PosX = 300.0f;		// 2番目のX座標
	static constexpr float kBg3PosX = -850.0f;		// 最前面のX座標
	static constexpr float kBgPosY = 50.0f;			// Y座標
	static constexpr float kBg3PosY = 55.0f;		// 最前面のY座標
	static constexpr float kBgPosZ = 200.0f;		// 最背面のZ座標
	static constexpr float kBg2PosZ = 150.0f;		// Z座標
	static constexpr float kBg3PosZ = 100.0f;		// 最前面のZ座標
};

