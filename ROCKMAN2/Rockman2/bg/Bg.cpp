#include "Bg.h"
#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>

namespace
{
	// マップチップ1つのサイズ
	constexpr int kChipWidth = 18;
	constexpr int kChipHeight = 18;

	// チップを置く数
	constexpr int kChipNumX = 120;
	constexpr int kChipNumY = 60;
	// マップチップ拡大率
	constexpr float kChipScale = 3.0f;

	// マップの広さ
	constexpr int kMapWidth = kChipWidth * kChipScale * kChipNumX;
	constexpr int kMapHeight = kChipHeight * kChipScale * kChipNumY;

	// マップチップの配列情報
	constexpr int kChipData[kChipNumY][kChipNumX] = { 0, 0 };
}

Bg::Bg() :
	m_pPlayer(nullptr),
	m_bgPos(0.0f, 0.0f),
	m_bgMove(0.0f),
	m_graphChipNumX(0),
	m_graphChipNumY(0),
	m_bgHandle(-1),
	m_bg2Handle(-1),
	m_bg3Handle(-1),
	m_bg4Handle(-1),
	m_mapHandle(-1)
{
}

Bg::~Bg()
{
}

void Bg::Init()
{
}

void Bg::Update()
{
}

void Bg::Draw()
{
}

//int Bg::GetScrollX()
//{
//	return 0;
//}
//
//int Bg::GetScrollY()
//{
//	return 0;
//}
//
//bool Bg::IsColPlayer()
//{
//	float playerLeft = m_pPlayer->GetColRect().GetLeft();
//	float playerRight = m_pPlayer->GetColRect().GetRight();
//	float playerTop = m_pPlayer->GetColRect().GetTop();
//	float playerBottom = m_pPlayer->GetColRect().GetBottom();
//
//	for (int y = 0; y < kChipNumY; y++)
//	{
//		for (int x = 0; x < kChipNumX; x++)
//		{
//			// 地面、床以外は当たらない
//			if (kChipData[y][x] == 0) continue;
//
//			int chipLeft = x * kChipWidth * kChipScale;
//			int chipRight = chipLeft + kChipWidth * kChipScale;
//			int chipTop = y * kChipHeight * kChipScale;
//			int chipBottom = chipTop + kChipHeight * kChipScale;
//
//			// 絶対に当たらない場合
//			if (chipLeft > playerRight) continue;
//			if (chipTop > playerBottom) continue;
//			if (chipRight < playerRight) continue;
//			if (chipBottom < playerTop) continue;
//
//			// いずれかのチップに当たっていたら終了する
//			return true;
//		}
//	}
//	/全てのチップをチェックして1つも当たっていなければ当たっていない
//	return false;
//}
//
//bool Bg::IsCollision(Rect rect, Rect& chipRect)
//{
//	for (int y = 0; y < kChipNumY; y++)
//	{
//		for (int x = 0; x < kChipNumX; x++)
//		{
//			// 地面、壁以外当たらない
//			if (kChipData[y][x] == 0) continue;
//
//			int chipLeft = x * kChipWidth * kChipScale;
//			int chipRight = chipLeft + kChipWidth * kChipScale;
//			int chipTop = y * kChipHeight * kChipScale;
//			int chipBottom = chipTop + kChipHeight * kChipScale;
//
//			// 絶対に当たらない場合
//			if (chipLeft > rect.GetRight()) continue;
//			if (chipTop > rect.GetBottom()) continue;
//			if (chipRight < rect.GetLeft()) continue;
//			if (chipBottom < rect.GetTop()) continue;
//
//			// ぶつかったマップチップの矩形を設定する
//			chipRect.m_left = static_cast<float>(chipLeft);
//			chipRect.m_right = static_cast<float>(chipRight);
//			chipRect.m_top = static_cast<float>(chipTop);
//			chipRect.m_bottom = static_cast<float>(chipBottom);
//
//			// いずれかのチップに当たっていたら終了する
//			return true;
//		}
//	}
//	// 全てのチップをチェックして1つも当たっていなければ当たっていない
//	return false;
//}
