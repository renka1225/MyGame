#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <vector>

class ShotBase;

/// <summary>
/// �G�̊��N���X
/// </summary>
class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Update() = 0;
	virtual void Draw() = 0;

	// �����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }
	// ���݂��Ă��邩�̔���		true:���݂��Ă���
	bool IsExist() const { return m_isExist; }
	// ���ݍ��W�̎擾
	Vec2 GetPos() const { return m_pos; }
	// �����蔻����擾����
	Rect GetColRect() const { return m_colRect; }

	// �G�L�����N�^�[���X�^�[�g������
	virtual void Start() = 0;

protected:
	// m_pos������ɁAm_handle�̃O���t�B�b�N�T�C�Y�𕝍����ɂ��������蔻���ݒ肷��
	virtual void UpdateCollision();

protected:
	// �V���b�g
	std::vector<ShotBase*> m_pShot;

	int m_handle;	// �O���t�B�b�N�̃n���h��
	bool m_isExist;	// ���݂��邩�t���O true:���݂���

	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��̋�`
	Rect m_colRect;
	// �ړ���
	Vec2 m_vec;
};

