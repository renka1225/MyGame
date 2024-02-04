#pragma once
#include "Vec2.h"
#include "Rect.h"
#include "Game.h"

class Player;
/// <summary>
/// �w�i�N���X
/// </summary>
class Bg
{
public:
	Bg();
	virtual ~Bg();

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	void DrawBg();
	// ��������̕\��
	void DrawEx(int scrollX, int scrollY);

	// �v���C���[�̈ʒu����X�N���[���ʂ����肷��
	int GetScrollX();
	int GetScrollY();

	// �v���C���[�̃|�C���^��ݒ�
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

	// �v���C���[�Ɠ������Ă��邩���肷��
	bool IsColPlayer();
	// �w�肵����`�Ɠ������Ă��邩���肷��
	bool IsCollision(Rect rect, Rect& chipRect);

protected:
	// �v���C���[�̃|�C���^
	Player* m_pPlayer;

	// �w�i�̕\���ʒu
	Vec2 m_bgPos;
	// �w�i�̈ړ���
	float m_bgMove;

	// �O���t�B�b�N�Ɋ܂܂��}�b�v�`�b�v�̐�
	int m_graphChipNumX;
	int m_graphChipNumY;

	// �w�i�̃O���t�B�b�N
	int m_bgHandle;	
	int m_bg2Handle;
	int m_bg3Handle;
	int m_bg4Handle;

	// �}�b�v�`�b�v�̃O���t�B�b�N
	int m_mapHandle;

	// ��������̉摜
	int m_walkHandle;		// �ړ�
	int m_jumpHandle;		// �W�����v
	int m_shotHandle;		// �V���b�g
	int m_metalHandle;		// ���^��
	int m_fireHandle;		// �t�@�C�A
	int m_lineHandle;		// 2��
	int m_menuHandle;		// ���j���[
	int m_recoveryHandle;	// �񕜃A�C�e��

	// �����摜�̃A�j���[�V����
	int m_exAnimFrame;
	int m_exFireAnimFrame;

	// �摜�T�C�Y
	struct Size
	{
		int width;
		int height;
	};
};