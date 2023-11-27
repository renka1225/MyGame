#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class Player;

class ShotBase
{
public:
	ShotBase();
	virtual ~ShotBase();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// �����o�[�ϐ��ɃA�N�Z�X����
	void SetMain(SceneMain* pMain) { m_pMain = pMain; }
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

	// �e�����݂��Ă��邩
	bool IsExist() const { return m_isExist; }
	// �����蔻��̋�`���擾����
	Rect GetColRect() const { return m_colRect; }

	// �e���X�^�[�g������
	// ���ˈʒu�������Ƃ��Ďw�肷��
	virtual void Start(Vec2 pos) = 0;

protected:
	// SceneMain�̊֐����Ăяo�����߂Ƀ|�C���^���o���Ă���
	SceneMain* m_pMain;
	// �V���b�g���������v���C���[�̃|�C���^���o���Ă���
	Player* m_pPlayer;

	// �e�����݂��邩�t���O(�g�p�����ǂ���)
	bool m_isExist;

	// �\���ʒu
	Vec2 m_pos;
	// �����蔻��̋�`
	Rect m_colRect;
	// �ړ���
	Vec2 m_vec;
};

