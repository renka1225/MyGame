#pragma once
#include "ShotBase.h"
class ShotLineMove : public ShotBase
{
public:
	ShotLineMove();
	virtual ~ShotLineMove();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	// �e���X�^�[�g������
	virtual void Start(Vec2 pos) override;

	// ���݂̃G�l���M�[�����擾����
	float GetLineMoveEnergy() const { return m_energy; }

private:
	// �O���t�B�b�N�̃n���h��
	int m_handle;
	// �Î~���鎞��
	int m_stopFrame;
	// ���݂̒e�G�l���M�[��
	float m_energy;
};

