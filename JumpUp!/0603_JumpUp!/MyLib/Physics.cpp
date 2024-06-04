#include "MyLib.h"
#include <cassert>

/// <summary>
/// �Փ˕��̓o�^
/// </summary>
/// <param name="collidable">�Փ˕�</param>
void Physics::Entry(Collidable* collidable)
{
	// �Փ˕���o�^����
	bool found = std::find(m_collidables.begin(), m_collidables.end(), collidable) != m_collidables.end();
	if (!found)
	{
		// �v�f�𖖔��ɒǉ�����
		m_collidables.emplace_back(collidable);
	}
	else // ���łɓo�^����Ă�����G���[
	{
		assert(0 && "�w���collidable�͓o�^�ςł�");
	}

}

/// <summary>
/// �Փ˕��̍폜
/// </summary>
/// <param name="collidable">�Փ˕�</param>
void Physics::Exit(Collidable* collidable)
{
	bool found = std::find(m_collidables.begin(), m_collidables.end(), collidable) != m_collidables.end();
	if (found)
	{
		m_collidables.remove(collidable);
	}
	else // �o�^����Ă��Ȃ�������G���[
	{
		assert(0 && "�w���collidable���o�^����Ă��܂���");
	}
}


/// <summary>
/// �X�V
/// </summary>
void Physics::Update()
{
	// �Փˏ��̍X�V�ƒʒm
	for (auto item : m_collidables)
	{
		// �ړ�
		auto pos = item->m_rigidbody.GetPos();
		auto nextPos = VAdd(pos, item->m_rigidbody.GetVelocity());
		
		//�f�o�b�O�\��
#ifdef _DEBUG
	
#endif

		item->m_rigidbody.SetPos(nextPos);
	}

	// �Փ˒ʒm�A�|�W�V�����␳���s��
	bool doCheck = true;
	int checkCount = 0;	// �`�F�b�N��
	while (doCheck)
	{
		doCheck = false;
		checkCount++;

		// 2�d���[�v�őS�I�u�W�F�N�g�̓����蔻��
		for (auto player : m_collidables)
		{
			for (auto ground : m_collidables)
			{
				if (player != ground)
				{
					// �v���C���[����Q���ɓ���������
					if (HitCube(player, ground))
					{
						printfDx("��������\n");
						auto pos1 = player->m_rigidbody.GetPos();
						auto pos2 = player->m_rigidbody.GetPos();

						// �|�W�V������␳����
						player->m_rigidbody.SetPos(VSub(pos1, pos2));

						// �Փ˒ʒm���s��
						//player->OnCollide();
						//ground->OnCollide();

						if (ground->GetTag() == Collidable::Tag::Ground)
						{
							player->m_rigidbody.SetPos(VAdd(player->m_rigidbody.GetPos(), VSub(player->m_rigidbody.GetPos(), ground->m_rigidbody.GetPos())));
						}
					}
				}
			}
		}
	}
}


/// <summary>
/// �����̂ƒ����̂̏Փ˔�����s��
/// </summary>
bool Physics::HitCube(Collidable* player, Collidable* ground)
{
	// TODO:������ӂ�Get����肭�s���ĂȂ��̂Œ���
	/*�v���C���[�ƒn�ʂ̓����蔻��*/
	// ���΃x�N�g�������߂�
	VECTOR v3SubAbs = VSub(player->m_rigidbody.GetPos(), ground->m_rigidbody.GetPos());
	v3SubAbs = VGet(abs(v3SubAbs.x), abs(v3SubAbs.y), abs(v3SubAbs.z));

	// �Փˋ��������߂�
	// �Փˋ����͂��ꂼ��̑Ή������ӂ̒����𑫂���2�Ŋ���������
	VECTOR v3AddScale = VScale(VAdd(player->m_rigidbody.GetScale(), ground->m_rigidbody.GetScale()), 0.5f);

	// �e�����̓����蔻��
	bool isXHit = v3SubAbs.x < v3AddScale.x;
	bool isYHit = v3SubAbs.y < v3AddScale.y;
	bool isZHit = v3SubAbs.z < v3AddScale.z;

	if (isXHit && isYHit && isZHit)
	{
		return true;
	}
	else
	{
		return false;
	}

}
