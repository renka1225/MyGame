#pragma once
#include "DxLib.h"

/// <summary>
/// �f�o�b�N�\���N���X
/// </summary>
class DrawDebug
{
public:
	// �O���b�h�\��
	void DrawGrid();
	// �v���C���[�̏���`��
	void DrawPlayerInfo(VECTOR pos);
	// �����̂̓����蔻���`��
	void DrawCubeCol(int handle, float angle, int color);
};