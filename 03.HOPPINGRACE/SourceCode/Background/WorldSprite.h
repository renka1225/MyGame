#pragma once
#include "DxLib.h"

/// <summary>
/// �X�v���C�g�\��
/// </summary>
class WorldSprite
{
public:
	void Init(int textureGraph, int width, int height, int spriteNo);
	void SetTransform(const VECTOR& pos, float spriteSize);
	void Draw();

private:
	int	textureGraph;	// �X�v���C�g���쐬����摜
	VECTOR pos;			// �`��|�W�V����
	VERTEX3D Vertex[4];	// ���_�o�b�t�@
	WORD Index[6];		// �C���f�b�N�X�o�b�t�@
};

