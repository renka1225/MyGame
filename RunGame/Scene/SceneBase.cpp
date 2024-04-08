#include "SceneBase.h"
#include "ManagerFont.h"

SceneBase::SceneBase():
	m_fadeAlpha(0)
{
	m_pFont = std::make_shared<ManagerFont>();
}
