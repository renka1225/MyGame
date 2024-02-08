#pragma once
#include "Bg.h"

/// <summary>
/// �`���[�g���A���̔w�i�N���X
/// </summary>
class BgTutorial : public Bg
{
public:
	BgTutorial();
	virtual ~BgTutorial();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	// �v���C���[�̈ʒu����X�N���[���ʂ����肷��
	virtual int GetScrollX() override;
	virtual int GetScrollY() override;
	// �v���C���[�Ɠ������Ă��邩���肷��
	virtual bool IsColPlayer() override;
	// �w�肵����`�Ɠ������Ă��邩���肷��
	virtual bool IsCollision(Rect rect, Rect& chipRect) override;

	// �w�i�`��
	void DrawBg();
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

