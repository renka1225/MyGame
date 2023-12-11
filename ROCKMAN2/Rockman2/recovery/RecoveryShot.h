#pragma once
#include "RecoveryBase.h"

/// <summary>
/// �e���񕜃N���X
/// </summary>
class RecoveryShot:public RecoveryBase
{
public:
	RecoveryShot();
	virtual ~RecoveryShot();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	// �e�����݂��Ă��邩
	bool IsExist() const { return m_isExist; }
	// �����蔻��̋�`���擾����
	Rect GetColRect() const { return m_colRect; }

private:
	// �O���t�B�b�N�̃n���h��
	int m_shotSmallRecHandle;	// �e����
	int m_shotGreatRecHandle;	// �e���

	// �e����
	float m_shotSmallRecovery; // ����
	float m_shotGreatRecovery; // ���

	// ��ʓ��ɑ��݂��邩
	bool m_isExist;
	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��̋�`
	Rect m_colRect;
};

