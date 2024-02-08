#include "Bg.h"
#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>

namespace
{
	// �}�b�v�`�b�v1�̃T�C�Y
	constexpr int kChipWidth = 18;
	constexpr int kChipHeight = 18;

	// �`�b�v��u����
	constexpr int kChipNumX = 120;
	constexpr int kChipNumY = 60;
	// �}�b�v�`�b�v�g�嗦
	constexpr float kChipScale = 3.0f;

	// �}�b�v�̍L��
	constexpr int kMapWidth = kChipWidth * kChipScale * kChipNumX;
	constexpr int kMapHeight = kChipHeight * kChipScale * kChipNumY;

	// �}�b�v�`�b�v�̔z����
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
//			// �n�ʁA���ȊO�͓�����Ȃ�
//			if (kChipData[y][x] == 0) continue;
//
//			int chipLeft = x * kChipWidth * kChipScale;
//			int chipRight = chipLeft + kChipWidth * kChipScale;
//			int chipTop = y * kChipHeight * kChipScale;
//			int chipBottom = chipTop + kChipHeight * kChipScale;
//
//			// ��΂ɓ�����Ȃ��ꍇ
//			if (chipLeft > playerRight) continue;
//			if (chipTop > playerBottom) continue;
//			if (chipRight < playerRight) continue;
//			if (chipBottom < playerTop) continue;
//
//			// �����ꂩ�̃`�b�v�ɓ������Ă�����I������
//			return true;
//		}
//	}
//	/�S�Ẵ`�b�v���`�F�b�N����1���������Ă��Ȃ���Γ������Ă��Ȃ�
//	return false;
//}
//
//bool Bg::IsCollision(Rect rect, Rect& chipRect)
//{
//	for (int y = 0; y < kChipNumY; y++)
//	{
//		for (int x = 0; x < kChipNumX; x++)
//		{
//			// �n�ʁA�ǈȊO������Ȃ�
//			if (kChipData[y][x] == 0) continue;
//
//			int chipLeft = x * kChipWidth * kChipScale;
//			int chipRight = chipLeft + kChipWidth * kChipScale;
//			int chipTop = y * kChipHeight * kChipScale;
//			int chipBottom = chipTop + kChipHeight * kChipScale;
//
//			// ��΂ɓ�����Ȃ��ꍇ
//			if (chipLeft > rect.GetRight()) continue;
//			if (chipTop > rect.GetBottom()) continue;
//			if (chipRight < rect.GetLeft()) continue;
//			if (chipBottom < rect.GetTop()) continue;
//
//			// �Ԃ������}�b�v�`�b�v�̋�`��ݒ肷��
//			chipRect.m_left = static_cast<float>(chipLeft);
//			chipRect.m_right = static_cast<float>(chipRight);
//			chipRect.m_top = static_cast<float>(chipTop);
//			chipRect.m_bottom = static_cast<float>(chipBottom);
//
//			// �����ꂩ�̃`�b�v�ɓ������Ă�����I������
//			return true;
//		}
//	}
//	// �S�Ẵ`�b�v���`�F�b�N����1���������Ă��Ȃ���Γ������Ă��Ȃ�
//	return false;
//}
