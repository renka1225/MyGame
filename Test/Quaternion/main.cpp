#include "DxLib.h"
#include "Quaternion.h"
#include <math.h>
#include <memory>

namespace
{
	constexpr float kCameraDist = 96;
	constexpr float kCameraHeight = 32;
	constexpr float kScale = 0.05f;
}

void DrawGrid()
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


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// window���[�h�ݒ�
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)	// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetUseBackCulling(true);

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	float cameraAngle = -DX_PI_F / 2;

	/*Cube���*/
	int m_handle = MV1LoadModel("data/cube.mv1");
	VECTOR m_pos = VGet(0.0f, 0.0f, 0.0f);
	// ��]�p�x
	float m_angle = 2 * DX_PI_F * 0.02f;
	// ��]��
	VECTOR m_axis = VGet(10.0f, 10.0f, 10.0f);
	// ���K��
	VNorm(m_axis);

	// ��]�N�H�[�^�j�I���쐬
	Quaternion q {0.0f, 0.0f, 0.0f, 0.0f};
	q.w = cos(m_angle / 2.0f);
	q.x = m_axis.x * sin(m_angle / 2.0f);
	q.y = m_axis.y * sin(m_angle / 2.0f);
	q.z = m_axis.z * sin(m_angle / 2.0f);

	MV1SetScale(m_handle, VGet(kScale, kScale, kScale));

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

		/*�J��������*/
		if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_5))
		{
			cameraAngle += 0.05f;
		}
		if ((GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_6))
		{
			cameraAngle -= 0.05f;
		}

		SetCameraNearFar(1.0f, 180.0f);
		VECTOR cameraPos;
		cameraPos.x = cosf(cameraAngle) * kCameraDist;
		cameraPos.y = kCameraHeight;
		cameraPos.z = sinf(cameraAngle) * kCameraDist;
		SetCameraPositionAndTarget_UpVecY(cameraPos, VGet(0, 0, 0));

		/*�O���b�h�\��*/
		DrawGrid();

		// �Q�[���̏���
		// ��]�p�x
		m_angle += 2 * DX_PI_F * 0.02f;

		// ��]�N�H�[�^�j�I���쐬
		q.w = cos(m_angle / 2.0f);
		q.x = m_axis.x * sin(m_angle / 2.0f);
		q.y = m_axis.y * sin(m_angle / 2.0f);
		q.z = m_axis.z * sin(m_angle / 2.0f);

		m_pos = q * m_pos;
		MV1SetPosition(m_handle, m_pos);
		MV1DrawModel(m_handle);

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DxLib_End();			// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}