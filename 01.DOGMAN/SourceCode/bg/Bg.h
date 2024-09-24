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

	virtual void Init() = 0;
	virtual	void Update() = 0;
	virtual void Draw() = 0;

	// �v���C���[�̈ʒu����X�N���[���ʂ����肷��
	virtual int GetScrollX() = 0;
	virtual int GetScrollY() = 0;
	// �v���C���[�Ɠ������Ă��邩���肷��
	virtual bool IsColPlayer() = 0;
	// �w�肵����`�Ɠ������Ă��邩���肷��
	virtual bool IsCollision(Rect rect, Rect& chipRect) = 0;

	// �v���C���[�̃|�C���^��ݒ�
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

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

	// �摜�T�C�Y
	struct Size
	{
		int width;
		int height;
	};
};