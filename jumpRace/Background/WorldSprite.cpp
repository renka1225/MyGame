#include "WorldSprite.h"


/// <summary>
/// ������
/// </summary>
/// <param name="textureGraph">�e�N�X�`���̉摜�n���h��</param>
/// <param name="width">�摜�̉���</param>
/// <param name="height">�摜�̏c��</param>
/// <param name="spriteNo">�X�v���C�g�ԍ�</param>
void WorldSprite::Init(int textureGraph, int width, int height, int spriteNo)
{
	this->textureGraph = textureGraph;

	// 4���_����uv�f�[�^��ݒ�
	int texW, texH;
	GetGraphTextureSize(textureGraph, &texW, &texH);
	int chipNumX = texW / width;
	int chipNoX = spriteNo % chipNumX;
	int chipNumY = texH / height;
	int chipNoY = spriteNo / chipNumY;
	float URate = 1.0f / static_cast<float>(chipNumX); // �e�N�X�`���S����1.0�Ƃ�������u�̃T�C�Y
	float VRate = 1.0f / static_cast<float>(chipNumY); // �e�N�X�`���S����1.0�Ƃ�������v�̃T�C�Y
	Vertex[0].u = (chipNoX + 0.0f) * URate;
	Vertex[0].v = (chipNoY + 0.0f) * VRate;
	Vertex[1].u = (chipNoX + 1.0f) * URate;
	Vertex[1].v = (chipNoY + 0.0f) * VRate;
	Vertex[2].u = (chipNoX + 0.0f) * URate;
	Vertex[2].v = (chipNoY + 1.0f) * VRate;
	Vertex[3].u = (chipNoX + 1.0f) * URate;
	Vertex[3].v = (chipNoY + 1.0f) * VRate;

	// �f�B�t���[�Y�A�X�y�L�����͏��������ɌŒ�
	for (int i = 0; i < 4; i++)
	{
		Vertex[i].dif = GetColorU8(255, 255, 255, 255);
		Vertex[i].spc = GetColorU8(0, 0, 0, 0);

		// ��]���T�|�[�g���Ȃ��̂Ńm�[�}�����Œ�
		Vertex[i].norm = VGet(0.0f, 0.0f, -1.0f);
		// �⏕�e�N�X�`�����T�|�[�g���Ȃ��̂�uv�Œ�
		Vertex[i].su = 0.0f;
		Vertex[i].sv = 0.0f;
	}

	// �Q�|���S�����̃C���f�b�N�X�f�[�^���Z�b�g
	Index[0] = 0;
	Index[1] = 1;
	Index[2] = 2;
	Index[3] = 3;
	Index[4] = 2;
	Index[5] = 1;
}


/// <summary>
/// �T�C�Y�ƃ|�W�V�����ɉ�����4���_���̒��_���W�𒲐�����
/// </summary>
/// <param name="pos">�|�W�V����</param>
/// <param name="spriteSize">�z�u���郏�[���h�X�v���C�g�̃T�C�Y</param>
void WorldSprite::SetTransform(const VECTOR& pos, float spriteSize)
{
	this->pos = pos;
	// �s�{�b�g���S�Őݒ�
	Vertex[0].pos = VScale(VGet(-1.0f, 1.0f, 0.0f), spriteSize * 0.5f);
	Vertex[1].pos = VScale(VGet(1.0f, 1.0f, 0.0f), spriteSize * 0.5f);
	Vertex[2].pos = VScale(VGet(-1.0, -1.0f, 0.0f), spriteSize * 0.5f);
	Vertex[3].pos = VScale(VGet(1.0f, -1.0f, 0.0f), spriteSize * 0.5f);
	for (int i = 0; i < 4; i++)
	{
		Vertex[i].pos = VAdd(Vertex[i].pos, pos);
	}
}


/// <summary>
/// �`��
/// </summary>
void WorldSprite::Draw()
{
	DrawPolygonIndexed3D(Vertex, 4, Index, 2, textureGraph, true);
}
