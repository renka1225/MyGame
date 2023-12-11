#pragma once
#include "RecoveryBase.h"


/// <summary>
/// HP�񕜃N���X
/// </summary>
class RecoveryHp : public RecoveryBase
{
public:
	RecoveryHp();
	virtual ~RecoveryHp();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Start() override;

	// �e�����݂��Ă��邩
	bool IsExist() const { return m_isExist; }
	// �����蔻��̋�`���擾����
	Rect GetColRect() const { return m_colRect; }

private:
	// �O���t�B�b�N�̃n���h��
	int m_hpSmallRecHandle;		// HP����
	int m_hpGreatRecHandle;		// HP���
	int m_hpFullRecHandle;		// HP�S��

	// ��ʓ��ɑ��݂��邩
	bool m_isExist;
	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��̋�`
	Rect m_colRect;
};

