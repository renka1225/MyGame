#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class Player;

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

	// �|�����G�̌��ݒn����A�C�e�����h���b�v����
	virtual void Start(Vec2 pos) = 0;

	// �A�C�e�������݂��Ă��邩
	bool IsExist() const { return m_isExist; }
	// �񕜃A�C�e���̓����蔻����擾����
	Rect GetColRect() const { return m_colRect; }
	// ���ݍ��W�̎擾
	Vec2 GetPos() const { return m_pos; }

protected:
	// �����蔻���ݒ肷��
	virtual void UpdateCollision();

protected:
	// �O���t�B�b�N�̃n���h��
	int m_handle;
	// ��ʓ��ɑ��݂��Ă��邩
	bool m_isExist;

	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��p�̋�`
	Rect m_colRect;
};

