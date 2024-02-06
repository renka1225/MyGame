#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneStage1;
class Bg;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player();
	~Player();

	// �}�b�v�̃|�C���^��ݒ肷��
	void SetBg(Bg* pBg) { m_pBg = pBg; }
	void SetStage(SceneStage1* pStage1) { m_pStage1 = pStage1; }

	void Init();
	void Update();
	void Draw();

	// �v���C���[�̕\��
	void DrawPlayer();
	// �}�b�v�`�b�v�Ƃ̓����蔻��̏���
	void CheckHitMap(Rect chipRect);

	// �v���C���[���_���[�W���󂯂����̏���
	void OnDamage();
	// �v���C���[��E�ʎ擾����
	void GetHpFullRecovery();
	// �v���C���[�̉񕜏���
	void HpSmallRecovery();		// HP����
	void HpGreatRecovery();		// HP���
	void ShotSmallRecovery();	// �e����
	void ShotGreatRecovery();	// �e���
	void LifeRecovery();		// �c�@��
	void HpFullRecovery();		// HP�S��

	// �A�C�e��2���ɏ�����ۂ̏���
	void RideLineMove(Rect shotRect);

	// ���݂̕���I����Ԃ��X�V����
	void ChangeShot(bool isBuster, bool isMetal, bool isFire, bool isLineMove);

public:
	// ���݈ʒu���X�V����
	void SetPos(Vec2 pos) { m_pos = pos; }
	// �v���C���[�̌��݂̌������擾����
	bool GetDir() const { return m_isRight; }
	// �v���C���[�̌��ݍ��W���擾����
	Vec2 GetPos() const { return m_pos; }
	// �v���C���[�̓����蔻����擾����
	Rect GetColRect() const { return m_colRect; }

	// ���݂�HP���擾����
	int GetHp() const { return m_hp; }
	// ���݂̎c�@�����擾����
	int GetLife() const { return m_life; }
	// ���݂�E�ʐ����擾
	int GetFullHpRecovery() const { return m_fullHpRecovery; }

	// ���݂̒e�G�l���M�[�����擾����
	float GetMetalEnergy() const { return m_metalEnergy; }
	float GetFireEnergy() const { return m_fireEnergy; }
	float GetLineEnergy() const { return m_lineEnergy; }

	// �t�@�C�A�̏�Ԃ��擾
	bool IsSmallFire() const { return m_isSmallFire; }
	bool IsMiddleFire() const { return m_isMiddleFire; }
	bool IsBigFire() const { return m_isBigFire; }

public:
	// ���킪�I�𒆂��擾����
	bool IsBuster() const { return m_isBuster; }	// �o�X�^�[
	bool IsMetal() const { return m_isMetal; }		// ���^��
	bool IsFire() const { return m_isFire; }		// �t�@�C�A
	bool IsLineMove() const { return m_isLineMove; }// 2��

private:
	// �w�i
	Bg* m_pBg;
	SceneStage1* m_pStage1;

	// �\���ʒu
	Vec2 m_pos;
	// �ړ���
	Vec2 m_move;
	// �����蔻��p�̋�`
	Rect m_colRect;

	// �����Ă������
	bool m_isRight;
	// �n�ʂƐڂ��Ă��邩
	bool m_isGround;	// true:�ڂ��Ă���
	// �W�����v����
	bool m_isJump;
	// �W�����v���̃t���[����
	int m_jumpFrame;

	// HP
	int m_hp;
	// �c�@
	int m_life;
	// E��
	int m_fullHpRecovery;

	// �_���[�W���󂯂Ă���̃t���[����
	int m_damageFrame;

	// ���^���̒e�G�l���M�[��
	float m_metalEnergy;
	// �t�@�C���[�̒e�G�l���M�[��
	float m_fireEnergy;
	// �A�C�e��2���̒e�G�l���M�[��
	float m_lineEnergy;

	// ����𑕔����Ă��邩
	bool m_isBuster; // �o�X�^�[
	bool m_isMetal;	 // ���^��
	bool m_isFire;	 // �t�@�C�A
	bool m_isLineMove; // 2��(�����ړ����鑫��)

	// �{�^���̏�Ԃ��擾����
	int m_keyState;
	// �{�^�������������ꂽ����
	int m_pressTime;
	// �{�^���������ė����܂ł̎���
	int m_nowPressTime;
	// �t�@�C�A�̃T�C�Y
	bool m_isSmallFire;		// ��
	bool m_isMiddleFire;	// ��
	bool m_isBigFire;		// ��
	// �A�C�e��2���̑ҋ@����
	int m_lineTime;

	// ��
	int m_shotSE;		// �V���b�g����SE
	int m_shotFireSE;	// �t�@�C�A���ߎ���SE
	int m_jumpSE;		// �W�����v����SE
	int m_damageSE;		// �_���[�W����SE
	int m_deadSE;		// ���S����SE

	// �摜
	int m_idleHandle;	// �ҋ@���
	int m_walkHandle;	// ����
	int m_shotHandle;	// �U��
	int m_jumpHandle;	// �W�����v
	int m_damageHandle;	// �_���[�W

	// �摜�̃A�j���[�V����
	enum Anim
	{
		kIdle,
		kWalk,
		kShot,
		kJump,
		kDamage
	};
	// ���݂̃A�j���[�V�������
	Anim m_animation;
	// �ҋ@�A�j���[�V����
	int m_idleAnimFrame;
	// �ړ��A�j���[�V����
	int m_walkAnimFrame;
	// �e�A�j���[�V����
	int m_shotAnimFrame;
	// �_���[�W�A�j���[�V����
	int m_damageAnimFrame;
};