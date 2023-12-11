#pragma once
#include "RecoveryBase.h"

/// <summary>
/// �c�@�񕜃N���X
/// </summary>
class RecoveryLife :public RecoveryBase
{
public:
	RecoveryLife();
	virtual ~RecoveryLife();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	// �e�����݂��Ă��邩
	bool IsExist() const { return m_isExist; }
	// �����蔻��̋�`���擾����
	Rect GetColRect() const { return m_colRect; }

private:
	// �O���t�B�b�N�̃n���h��
	int m_lifeRecHandle;

	// �c�@��
	int m_lifeRecovery;

	// ��ʓ��ɑ��݂��邩
	bool m_isExist;
	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��̋�`
	Rect m_colRect;

};

