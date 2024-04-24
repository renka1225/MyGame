#include "SceneBase.h"
#include "ManagerFont.h"
#include "ManagerSound.h"
#include "ManagerResult.h"
#include "DxLib.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneBase::SceneBase()
{
	m_pFont = std::make_shared<ManagerFont>();
	m_pSound = std::make_shared<ManagerSound>();
	m_pResult = std::make_shared<ManagerResult>();
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneBase::~SceneBase()
{
}
