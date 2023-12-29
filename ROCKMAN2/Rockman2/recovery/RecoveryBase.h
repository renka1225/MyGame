#pragma once
#include "Vec2.h"
#include "Rect.h"

class Player;
class SceneMain;

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
	// ���ݍ��W�̎擾
	Vec2 GetPos() const { return m_pos; }
	// �񕜃A�C�e���̓����蔻����擾����
	Rect GetColRect() const { return m_colRect; }

protected:
	// �����蔻���ݒ肷��
	virtual void UpdateCollision();

protected:
	// ���C���V�[���̃|�C���^
	SceneMain* m_pMain;

	// �O���t�B�b�N�̃n���h��
	int m_handle;
	// ��ʓ��ɑ��݂��Ă��邩
	bool m_isExist;
	// �\������
	int m_frame;

	// �\���ʒu
	Vec2 m_pos;
	// �ړ���
	Vec2 m_vec;
	// �����蔻��p�̋�`
	Rect m_colRect;
};

