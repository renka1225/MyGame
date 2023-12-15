#include "RecoveryBase.h"

RecoveryBase::RecoveryBase():
	m_pEnemy(nullptr),
	m_pMain(nullptr),
	m_isExist(false)
{
}

RecoveryBase::~RecoveryBase()
{
}

void RecoveryBase::Init()
{
}

void RecoveryBase::Update()
{
	// 存在しないアイテムの処理はしない
	if (!m_isExist) return;
}

void RecoveryBase::Draw()
{
	// 存在しないアイテムの描画はしない
	if (!m_isExist) return;
}