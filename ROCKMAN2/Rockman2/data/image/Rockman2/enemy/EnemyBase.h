#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <vector>

class RecoveryBase;
class ShotBase;
class Bg;
class SceneMain;

/// <summary>
/// �G�̊��N���X
/// </summary>
class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Init();
	virtual void Update();
	virtual void Draw();

	// �G���_���[�W���󂯂����̏���
	virtual void OnDamage();
	// �G�L�����N�^�[���X�^�[�g������
	virtual void Start(float posX, float posY ) = 0;

	// �����o�[�ϐ��ɃA�N�Z�X����
	void SetMain(SceneMain* pMain) { m_pMain = pMain; }
	void SetBg(Bg* pBg) { m_pBg = pBg; }

	// ���݂��Ă��邩�̔���		true:���݂��Ă���
	bool IsExist() const { return m_isExist; }
	// �G���|���ꂽ���擾
	bool IsDead() const { return m_isDead; }
	// HP�̎擾
	int GetHp() const { return m_hp; }
	// ���ݍ��W�̎擾
	Vec2 GetPos() const { return m_pos; }
	// �����蔻����擾����
	Rect GetColRect() const { return m_colRect; }

protected:
	// ���C���V�[���̃|�C���^
	SceneMain* m_pMain;
	// �w�i�N���X�̃|�C���^
	Bg* m_pBg;
	// �񕜃A�C�e���̃|�C���^
	RecoveryBase* m_pRecovery;
	// �V���b�g�̃|�C���^
	std::vector<ShotBase*> m_pShot;

	// �O���t�B�b�N�̃n���h��
	int m_handle;
	// ���݂��邩�t���O true:���݂���
	bool m_isExist;	
	// �G��HP
	int m_hp;
	// �G���|���ꂽ���ǂ��� // true:�|���ꂽ
	bool m_isDead;

	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��̋�`
	Rect m_colRect;
	// �ړ���
	Vec2 m_vec;

	// �����Ă������
	enum Dir
	{
		kDirLeft,	// ��
		kDirRight,	// �E
	};

	// �����Ă������
	Dir m_dir;
};
