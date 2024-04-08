#include "SceneBase.h"
#include "ManagerFont.h"

SceneBase::SceneBase()
{
	m_pFont = std::make_shared<ManagerFont>();
}