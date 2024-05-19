#include "DxLib.h"
#include "Cube.h"
#include "Cube2.h"
#include "Sphere.h"
#include "Sphere2.h"
#include "Capsule.h"
#include "Capsule2.h"
#include "Triangle.h"
#include "Plane.h"
#include <cmath>
#include <memory>

namespace
{
	constexpr float kCameraDist = 96;
	constexpr float kCameraHeight = 32;
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

	// �|�C���^
	std::shared_ptr<Plane> pPlane = std::make_shared<Plane>();
	std::shared_ptr<Cube2> pCube2 = std::make_shared<Cube2>();
	std::shared_ptr<Cube> pCube = std::make_shared<Cube>(pPlane, pCube2);
	std::shared_ptr<Sphere2> pSphere2 = std::make_shared<Sphere2>();
	std::shared_ptr<Capsule2> pCapsule2 = std::make_shared<Capsule2>();
	std::shared_ptr<Capsule> pCapsule = std::make_shared<Capsule>(pCapsule2);
	std::shared_ptr<Triangle> pTriangle = std::make_shared<Triangle>();
	std::shared_ptr<Sphere> pSphere = std::make_shared<Sphere>(pSphere2, pCapsule2, pTriangle);

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

		/*3D���f���̍X�V*/
		pCube->Update();
		//pSphere->Update();
		//pCapsule->Update();
		pPlane->Update();

		/*3D���f���\��*/
		// �����̂�\��
		pCube->Draw();
		//pCube2->Draw();

		// ����\��
		//pSphere->Draw();
		//pSphere2->Draw();

		// �J�v�Z����\��
		//pCapsule->Draw();
		//pCapsule2->Draw();

		// �O�p�`��\��
		//pTriangle->Draw();

		// ���ʂ�\��
		pPlane->Draw();

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}