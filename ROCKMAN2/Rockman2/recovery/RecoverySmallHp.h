#pragma once
#include "RecoveryBase.h"

/// <summary>
/// HP���񕜃N���X
/// </summary>
class RecoverySmallHp : public RecoveryBase
{
public:
	RecoverySmallHp();
	virtual ~RecoverySmallHp();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	// �A�C�e�����h���b�v����
	virtual void Start(Vec2 pos) override;

	// �e�����݂��Ă��邩
	bool IsExist() const { return m_isExist; }
	// �����蔻��̋�`���擾����
	Rect GetColRect() const { return m_colRect; }

private:
	// �O���t�B�b�N�̃n���h��
	int m_hpSmallRecHandle;
	// ��ʓ��ɑ��݂��邩
	bool m_isExist;
	// �\�����Ԃ̃t���[��
	int m_frame;
	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��̋�`
	Rect m_colRect;
	// �ړ���
	Vec2 m_vec;
};

