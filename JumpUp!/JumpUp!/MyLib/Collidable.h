#pragma once

class Rigidbody;
class Physics;

/// <summary>
/// �Փ˂ł��镨�̂̊��N���X
/// </summary>
class Collidable
{
public:
	// �����������̂̔��ʂ��s��
	enum class Tag
	{
		Player,	// �v���C���[
		Floor	// ��
	};

	Collidable(Tag tag);
	// �Փ˂����ۂ̏���
	virtual void OnCollide() = 0;

	Tag GetTag() const { return m_tag; }

protected:
	Rigidbody m_rigidbody;

private:
	Tag m_tag;

	// Physics��Collidable�����R�ɊǗ����邽�߂Ƀt�����h��
	friend Physics;
};

