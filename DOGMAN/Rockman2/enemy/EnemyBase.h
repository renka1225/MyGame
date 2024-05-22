#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <vector>

class RecoveryBase;
class ShotBase;
class Bg;
class Player;
class SceneMain;

/// <summary>
/// �G�̊��N���X
/// </summary>
class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Init(Bg* pBg, Player* pPlayer);
	virtual void Update();
	virtual void Draw();

	// �G���_���[�W���󂯂����̏���
	virtual void OnDamage();
	// �}�b�v�`�b�v�Ƃ̓����蔻��
	virtual void HitCollision(Rect chipRect);
	// �G�L�����N�^�[���X�^�[�g������
	virtual void Start(float posX, float posY, float moveRangeX) = 0;

	// �����o�[�ϐ��ɃA�N�Z�X����
	void SetMain(SceneMain* pMain) { m_pMain = pMain; }

	// ���݂��Ă��邩�̔���		true:���݂��Ă���
	bool IsExist() const { return m_isExist; }
	// �G���|���ꂽ���擾
	bool IsDead() const { return m_isDead; }
	// HP�̎擾
	float GetHp() const { return m_hp; }
	// ���ݍ��W�̎擾
	Vec2 GetPos() const { return m_pos; }
	// �����蔻����擾����
	Rect GetColRect() const { return m_colRect; }

protected:
	// ���C���V�[���̃|�C���^
	SceneMain* m_pMain;
	// �w�i�N���X�̃|�C���^
	Bg* m_pBg;
	// �v���C���[�̃|�C���^
	Player* m_pPlayer;
	// �񕜃A�C�e���̃|�C���^
	RecoveryBase* m_pRecovery;
	// �V���b�g�̃|�C���^
	std::vector<ShotBase*> m_pShot;

	// �O���t�B�b�N�̃n���h��
	int m_handle;

	// ���݂��邩�t���O true:���݂���
	bool m_isExist;	
	// �G��HP
	float m_hp;
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
	Dir m_dir;

	// �X�^�[�g���̓G�̍��W
	Vec2 m_startPos;
	// ���̈ړ��͈�
	float m_moveRangeX;

	// ��
	int m_damageSE;	// �_���[�W����SE

	// �_���[�W�G�t�F�N�g
	int m_damageEffect; // �_���[�W���̃G�t�F�N�g
	int m_damageFrame;	// �G�t�F�N�g�̃A�j���[�V����
};