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
	// ���݂��Ȃ��A�C�e���̏����͂��Ȃ�
	if (!m_isExist) return;

	// 10�b�ȏソ������A�C�e��������
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
	// �����蔻��̕\��
	m_colRect.Draw(0x0000ff, false);
#endif
}
