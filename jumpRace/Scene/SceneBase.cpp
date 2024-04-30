#include "SceneBase.h"
#include "ManagerFont.h"
#include "ManagerSound.h"
#include "ManagerResult.h"
#include "DxLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
SceneBase::SceneBase()
{
	m_pFont = std::make_shared<ManagerFont>();
	m_pSound = std::make_shared<ManagerSound>();
	m_pResult = std::make_shared<ManagerResult>();

	m_buttonHandle = LoadGraph("data/UI/button.png");
}


/// <summary>
/// デストラクタ
/// </summary>
SceneBase::~SceneBase()
{
	DeleteGraph(m_buttonHandle);
}