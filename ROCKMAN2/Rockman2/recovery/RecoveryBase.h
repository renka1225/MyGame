#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class EnemyBase;
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

	// �A�C�e�����h���b�v����
	virtual void Start(Vec2 pos) = 0;

	// �����o�ϐ��ɃA�N�Z�X����
	void SetMain(SceneMain* pMain) { m_pMain = pMain; }
	void SetEnemy(EnemyBase* pEnemy) { m_pEnemy = pEnemy; }

	// �A�C�e�������݂��Ă��邩
	bool IsExist() const { return m_isExist; }
	// �񕜃A�C�e���̓����蔻����擾����
	Rect GetColRect() const { return m_colRect; }
	// ���ݍ��W�̎擾
	Vec2 GetPos() const { return m_pos; }

private:
	// SceneMain�̊֐����Ăяo�����߂Ƀ|�C���^���o���Ă���
	SceneMain* m_pMain;
	// �A�C�e�����h���b�v����G�̃|�C���^���o���Ă���
	EnemyBase* m_pEnemy;

	// ��ʓ��ɑ��݂��Ă��邩
	bool m_isExist;

	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��p�̋�`
	Rect m_colRect;
};

