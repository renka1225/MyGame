#include "DrawDebug.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
DrawDebug::DrawDebug()
{
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
DrawDebug::~DrawDebug()
{
}


/// <summary>
/// �����̂̓����蔻��`��
/// </summary>
/// <param name="pos">�����̂̈ʒu</param>
/// <param name="width">�����̂̉���</param>
/// <param name="height">�����̂̏c��</param>
/// <param name="depth">�����̂̉��s��</param>
/// <param name="color">�����蔻��̐F</param>
void DrawDebug::DrawCubeCol(VECTOR pos, float width, float height, float depth, int color)
{
	//VECTOR pos1 = VSub(pos, VGet(width, height, depth));
	VECTOR pos1 = VGet(pos.x - width * 0.5f, pos.y + height * 0.5f, pos.z - depth * 0.5f);
	VECTOR pos2 = VGet(pos.x + width * 0.5f, pos.y - height * 0.5f, pos.z + depth * 0.5f);
	DrawCube3D(pos1, pos2, color, 0x000000, false);
}
