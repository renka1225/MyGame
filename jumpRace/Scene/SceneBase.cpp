#include "SceneBase.h"
#include "ManagerFont.h"
#include "ManagerSound.h"
#include "DxLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneBase::SceneBase()
{
	//m_pFont = std::make_shared<ManagerFont>();
	m_pSound = std::make_shared<ManagerSound>();
}


/// <summary>
/// デストラクタ
/// </summary>
SceneBase::~SceneBase()
{
}
