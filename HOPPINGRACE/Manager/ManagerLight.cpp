#include "ManagerLight.h"
#include "DxLib.h"


/// <summary>
/// コンストラクタ
/// </summary>
ManagerLight::ManagerLight():
	m_dirLightHandle(-1)
{
}


/// <summary>
/// ディレクショナルタイプのライトハンドルを作成する
/// </summary>
void ManagerLight::CreateDirLight()
{
	m_dirLightHandle = CreateDirLightHandle(VGet(kDirLightPosX, kDirLightPosY, kDirLightPosZ));
}


/// <summary>
/// ディレクショナルタイプのライトハンドルを削除する
/// </summary>
void ManagerLight::DeleteDirLight()
{
	DeleteLightHandle(m_dirLightHandle);
}
