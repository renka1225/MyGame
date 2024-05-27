#pragma once
#include <list>

class Collidable;

/// <summary>
/// �Փ˔��肷��I�u�W�F�N�g��o�^���A�����ړ��E�Փ˂�ʒm����N���X
/// </summary>
class Physics
{
public:
	void Entry(Collidable* collidable);		// �Փ˕��̓o�^
	void Exit(Collidable* collidable);		// �Փ˕��̓o�^����
	void Update();

private:
	// �����̂ƒ����̂̓����蔻����s��
	bool HitCube();

private:
	// �o�^���ꂽCollidable�̃��X�g
	std::list<Collidable*> m_collidables;
};

