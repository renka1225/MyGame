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
	// �w�i�`��
	void DrawBg();
	// �v���C���[�̈ʒu����X�N���[���ʂ����肷��
	int GetScrollX();
	int GetScrollY();
	// �v���C���[�Ɠ������Ă��邩���肷��
	bool IsColPlayer();
	// �w�肵����`�Ɠ������Ă��邩���肷��
	bool IsCollision(Rect rect, Rect& chipRect);
};