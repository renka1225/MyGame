#include "RecoveryBase.h"
#include "Player.h"
#include "SceneMain.h"
#include "Bg.h"
#include "DxLib.h"

RecoveryBase::RecoveryBase():
	m_pMain(nullptr),
	m_pBg(nullptr),
	m_handle(-1),
	m_frame(0),
	m_isExist(false)
{
}

RecoveryBase::~RecoveryBase()
{
}

void RecoveryBase::Init(Bg* pBg)
{
	m_pBg = pBg;
	m_isExist = false;
}

void RecoveryBase::Update()
{
	// ë∂ç›ÇµÇ»Ç¢ÉAÉCÉeÉÄÇÃèàóùÇÕÇµÇ»Ç¢
	if (!m_isExist) return;
}

void RecoveryBase::Draw()
{
}
