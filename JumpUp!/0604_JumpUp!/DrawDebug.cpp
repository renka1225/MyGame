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
/// <param name="pos">�v���C���[�̍��W</param>
void DrawDebug::DrawPlayerInfo(VECTOR pos)
{
	DrawFormatString(0, 40, 0xffffff, "Player���W(x:%f, y:%f, z:%f)", pos.x, pos.y, pos.z);
}


/// <summary>
/// �����̂̓����蔻���`��
/// </summary>
/// <param name="handle">���f���̃n���h��</param>
void DrawDebug::DrawCubeCol(int handle, float angle, int color)
{
	// ���f���̏����擾
	VECTOR pos = MV1GetPosition(handle);		// ���W
	VECTOR scale = MV1GetScale(handle);			// �T�C�Y
	VECTOR halfScale = VScale(scale, 0.5f);		// ���a

	VECTOR pos1 = VSub(pos, halfScale);	// �����O�̍��W
	VECTOR pos2 = VAdd(pos, halfScale);	// �E�����̍��W

	DrawCube3D(pos1, pos2, color, 0x000000, false);
}