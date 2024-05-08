#include "ManagerLight.h"
#include "DxLib.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
ManagerLight::ManagerLight():
	m_dirLightHandle(-1)
{
}


/// <summary>
/// �f�B���N�V���i���^�C�v�̃��C�g�n���h�����쐬����
/// </summary>
void ManagerLight::CreateDirLight()
{
	m_dirLightHandle = CreateDirLightHandle(VGet(kDirLightPosX, kDirLightPosY, kDirLightPosZ));
}


/// <summary>
/// �f�B���N�V���i���^�C�v�̃��C�g�n���h�����폜����
/// </summary>
void ManagerLight::DeleteDirLight()
{
	DeleteLightHandle(m_dirLightHandle);
}
