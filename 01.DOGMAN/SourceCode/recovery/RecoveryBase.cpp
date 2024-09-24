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
	// 存在しないアイテムの処理はしない
	if (!m_isExist) return;

	// 10秒以上たったらアイテムを消す
	m_frame++;
	if (m_frame > 600)
	{
		m_isExist = false;
		m_frame = 0;
	}
}

void RecoveryBase::Draw()
{
#ifdef _DEBUG
	// 当たり判定の表示
	m_colRect.Draw(0x0000ff, false);
#endif
}
