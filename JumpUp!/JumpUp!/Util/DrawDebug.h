#pragma once
#include "DxLib.h"
#include "Player.h"

class Player;

/// <summary>
/// �f�o�b�N�\���N���X
/// </summary>
class DrawDebug
{
public:
	// �O���b�h�\��
	void DrawGrid();
	// �v���C���[�̏���`��
	void DrawPlayerInfo(VECTOR pos, Player::State state);
	// �J�����̏���`��
	void DrawCameraInfo(VECTOR pos, VECTOR target);
	// �^�C���\��
	void DrawTime(int frame);
};