#pragma once

/// <summary>
/// ���C�g�Ǘ��N���X
/// </summary>
class ManagerLight
{
public:
	ManagerLight();
	void CreateDirLight();	// �f�B���N�V���i���^�C�v�̃��C�g�n���h�����쐬����
	void DeleteDirLight();	// �f�B���N�V���i���^�C�v�̃��C�g�n���h�����폜

private:
	int m_dirLightHandle;	// �f�B���N�V���i���^�C�v�̃��C�g

private:	// �萔
	static constexpr float kDirLightPosX = 0.0f;
	static constexpr float kDirLightPosY = 0.0f;
	static constexpr float kDirLightPosZ = -7.0f;
};

