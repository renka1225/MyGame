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
	void DrawCubeCol(VECTOR pos, float width, float height, float depth, int color);
};

