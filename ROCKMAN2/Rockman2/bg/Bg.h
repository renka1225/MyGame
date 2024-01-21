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
	// �V�[�����C���̃|�C���^
	Player* m_pPlayer;

	// �w�i�̃O���t�B�b�N
	int m_bgHandle;
	// �}�b�v�`�b�v�̃O���t�B�b�N
	int m_mapHandle;

	// �w�i�̕\���ʒu
	Vec2 m_bgPos;

	// �O���t�B�b�N�Ɋ܂܂��}�b�v�`�b�v�̐�
	int m_graphChipNumX;
	int m_graphChipNumY;
};