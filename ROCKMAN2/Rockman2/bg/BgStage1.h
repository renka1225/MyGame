#pragma once
#include "Bg.h"

class Bg;

/// <summary>
/// �X�e�[�W1�̔w�i�N���X
/// </summary>
class BgStage1 : public Bg
{
public:
	BgStage1();
	virtual ~BgStage1();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void DrawBg() override;

	// �v���C���[�̈ʒu����X�N���[���ʂ����肷��
	int GetScrollX();
	int GetScrollY();
	// �v���C���[�Ɠ������Ă��邩���肷��
	bool IsColPlayer();
	// �w�肵����`�Ɠ������Ă��邩���肷��
	bool IsCollision(Rect rect, Rect& chipRect);

private:
	// ��������̕\��
	void DrawEx(int scrollX, int scrollY);

private:
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
};