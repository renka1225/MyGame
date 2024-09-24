#include "SceneBase.h"
#include "ManagerFont.h"
#include "ManagerSound.h"
#include "DxLib.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneBase::SceneBase():
	m_cursorPosY(700)
{
	m_pFont = std::make_shared<ManagerFont>();
	m_pSound = std::make_shared<ManagerSound>();

	m_cursorHandle = LoadGraph("data/UI/cursor.png");
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneBase::~SceneBase()
{
	DeleteGraph(m_cursorHandle);
}
