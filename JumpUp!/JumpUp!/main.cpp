#include "DxLib.h"
#include "SceneManager.h"
#include "Game.h"
#include "Input.h"
#include "Font.h"
#include <memory>
#include <cmath>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("JumpUp!");

	// window���[�h�ݒ�
	ChangeWindowMode(true);
	// ��ʃT�C�Y�ύX
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)	// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// Z�o�b�t�@�̐ݒ�
	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);
	SetUseBackCulling(true);

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	// SceneManager�𐶐�
	std::shared_ptr<SceneManager> pScene = std::make_shared<SceneManager>();
	pScene->Init();

	// ���͏�Ԃ��擾
	Input input;

	// �t�H���g�̓ǂݍ���
	Font::Load();

	SetLightPosition(VGet(0.0f, 10.0f, 0.0f));

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

		// �X�V
		input.Update();
		pScene->Update(input);

		// �`��
		pScene->Draw();

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667) {}
	}

	// �t�H���g�̉��
	Font::UnLoad();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}