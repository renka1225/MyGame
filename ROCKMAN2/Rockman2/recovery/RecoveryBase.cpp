#include "RecoveryBase.h"

RecoveryBase::RecoveryBase():
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
	// ���݂��Ȃ��A�C�e���̏����͂��Ȃ�
	if (!m_isExist) return;
}

void RecoveryBase::Draw()
{
	// ���݂��Ȃ��A�C�e���̕`��͂��Ȃ�
	if (!m_isExist) return;
}