#pragma once
#include "Bg.h"

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
	// �w�i�`��
	void DrawBg();
	// �v���C���[�̈ʒu����X�N���[���ʂ����肷��
	virtual int GetScrollX() override;
	virtual int GetScrollY() override;
	// �v���C���[�Ɠ������Ă��邩���肷��
	virtual bool IsColPlayer() override;
	// �w�肵����`�Ɠ������Ă��邩���肷��
	virtual bool IsCollision(Rect rect, Rect& chipRect) override;
};