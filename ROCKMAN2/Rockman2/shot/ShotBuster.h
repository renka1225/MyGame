#pragma once
#include "ShotBase.h"
#include <vector>

class ShotBuster : public ShotBase
{
public:
	ShotBuster();
	virtual ~ShotBuster();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	// �e���X�^�[�g������
	virtual void Start(Vec2 pos) override;

	// �����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }

private:
	// �O���t�B�b�N�̃n���h��
	int m_handle;
};

