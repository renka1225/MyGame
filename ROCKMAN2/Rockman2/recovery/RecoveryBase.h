#pragma once
#include "Vec2.h"
#include "Rect.h"

/// <summary>
/// �񕜃A�C�e�����N���X
/// </summary>
class RecoveryBase
{
public:
	RecoveryBase();
	virtual ~RecoveryBase();

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Start();

	// �A�C�e�������݂��Ă��邩
	bool IsExist() const { return m_isExist; }
	// �񕜃A�C�e���̓����蔻����擾����
	Rect GetColRect() const { return m_colRect; }
	// ���ݍ��W�̎擾
	Vec2 GetPos() const { return m_pos; }

private:
	// ��ʓ��ɑ��݂��Ă��邩
	bool m_isExist;

	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��p�̋�`
	Rect m_colRect;
};

