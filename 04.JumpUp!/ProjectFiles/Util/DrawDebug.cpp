#include "DrawDebug.h"
#include "ConversionTime.h"

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
///  <param name="state">���݂̃v���C���[�̏��</param>
void DrawDebug::DrawPlayerInfo(VECTOR pos, Player::State state)
{
	DrawFormatString(0, 40, 0xffffff, "Player���W(x:%f, y:%f, z:%f)", pos.x, pos.y, pos.z);

	// ���݂̏�Ԃ�`��
	if (state == Player::State::kStand)
	{
		DrawString(0, 60, "�ҋ@��", 0xffffff);
	}
	if (state == Player::State::kRun)
	{
		DrawString(0, 60, "�ړ���", 0xffffff);
	}
	if (state == Player::State::kJump)
	{
		DrawString(0, 60, "�W�����v��", 0xffffff);
	}
	if (state == Player::State::kFall)
	{
		DrawString(0, 60, "������", 0xffffff);
	}
}


/// <summary>
/// �J�����̏���`��
/// </summary>
/// <param name="pos">�J�������W</param>
/// <param name="target">�J�����̒����_���W</param>
void DrawDebug::DrawCameraInfo(VECTOR pos, VECTOR target)
{
	DrawFormatString(0, 60, 0xffffff, "�J�������W(x:%f, y:%f, z:%f)", pos.x, pos.y, pos.z);
	DrawFormatString(0, 80, 0xffffff, "�����_���W(x:%f, y:%f, z:%f)", target.x, target.y, target.z);
}


/// <summary>
/// �^�C����\������
/// </summary>
/// <param name="time">�o�ߎ���</param>
void DrawDebug::DrawTime(int frame)
{
	DrawFormatString(0, 80, 0xffffff, "�^�C��:%02d:%02d:%03d", 
		Conversion::ChangeMin(frame), Conversion::ChangeSec(frame), Conversion::ChangeMilliSec(frame));
}
