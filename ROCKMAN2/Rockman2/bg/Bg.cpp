#include "Bg.h"
#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>

Bg::Bg() :
	m_pPlayer(nullptr),
	m_bgPos(0, 0),
	m_graphChipNumX(0),
	m_graphChipNumY(0)
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

int Bg::GetScrollX()
{
	return 0;
}

int Bg::GetScrollY()
{
	return 0;
}

bool Bg::IsColPlayer()
{
	return false;
}

bool Bg::IsCollision(Rect rect, Rect& chipRect)
{
	return false;
}
