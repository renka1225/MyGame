#include "RecoveryBase.h"
#include "Player.h"]
#include "SceneMain.h"
#include "DxLib.h"

RecoveryBase::RecoveryBase():
	m_pMain(nullptr),
	m_handle(-1),
	m_isExist(false),
	m_frame(0),
	m_pos(0,0)
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
}

void RecoveryBase::UpdateCollision()
{
	int width = 0;
	int height = 0;
	GetGraphSize(m_handle, &width, &height);

	// �����蔻��𐶐�
	m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(width), static_cast<float>(height));
}
