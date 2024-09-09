#pragma once
#include "ShotBase.h"
#include <vector>

class ShotFire : public ShotBase
{
public:
	ShotFire();
	virtual ~ShotFire();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	// �e���X�^�[�g������
	virtual void Start(Vec2 pos) override;

private:
	// �O���t�B�b�N�̃n���h��
	int m_fire1Handle;	// �e1
	int m_fire2Handle;	// �e2
	int m_fire3Handle;	// �e3
};

