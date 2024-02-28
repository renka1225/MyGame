#include "Bg.h"
#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>

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