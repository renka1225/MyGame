#include "DrawDebug.h"


/// <summary>
/// �O���b�h�\��
/// </summary>
void DrawDebug::DrawGrid()
{
	for (int x = -50; x <= 50; x += 10)
	{
		DrawLine3D(VGet(static_cast<float>(x), 0, -50), VGet(static_cast<float>(x), 0, 50), 0xffff00);
	}
	for (int z = -50; z <= 50; z += 10)
	{
		DrawLine3D(VGet(-50, 0, static_cast<float>(z)), VGet(50, 0, static_cast<float>(z)), 0xff0000);
	}

	// X+-,Z+-�̕�����������₷���悤�ɕ\����ǉ�����
	VECTOR dispPos = ConvWorldPosToScreenPos(VGet(50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(-50, 0, 0));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "X-", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, 50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z+", 0xffffff);
	}

	dispPos = ConvWorldPosToScreenPos(VGet(0, 0, -50));
	if (dispPos.z >= 0.0f && dispPos.z <= 1.0f)
	{
		DrawStringF(dispPos.x, dispPos.y, "Z-", 0xffffff);
	}
}


/// <summary>
/// �v���C���[�̏���`��
/// </summary>
/// <param name="pos"></param>
void DrawDebug::DrawPlayerInfo(VECTOR pos)
{
	DrawFormatString(0, 20, 0xffffff, "Player���W(x:%f, y:%f, z:%f)", pos.x, pos.y, pos.z);
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
	VECTOR pos1 = VGet(pos.x - width * 0.5f, pos.y + height * 0.5f, pos.z - depth * 0.5f);
	VECTOR pos2 = VGet(pos.x + width * 0.5f, pos.y - height * 0.5f, pos.z + depth * 0.5f);
	DrawCube3D(pos1, pos2, color, 0x000000, false);
}
