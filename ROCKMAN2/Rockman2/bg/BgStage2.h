#pragma once
#include "Vec2.h"
#include "Rect.h"
#include "Game.h"
#include "Bg.h"

class Bg;

/// <summary>
/// �w�i�N���X
/// </summary>
class BgStage2 : public Bg
{
public:
	BgStage2();
	virtual ~BgStage2();

	virtual void Init () override;
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
};