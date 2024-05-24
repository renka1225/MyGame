#pragma once
#include <list>

class Collidable;

/// <summary>
/// �Փ˔��肷��I�u�W�F�N�g��o�^���A�����ړ��E�Փ˂�ʒm����N���X
/// </summary>
class Physics
{
public:
	// �Փ˕��̓o�^
	void Entry(Collidable* collidable);
	// �Փ˕��̓o�^����
	void Exit(Collidable* collidable);

	void Update();

private:
	// �o�^���ꂽCollidable�̃��X�g
	std::list<Collidable*> Collidables;
};

