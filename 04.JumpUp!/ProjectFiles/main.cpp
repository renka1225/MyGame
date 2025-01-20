#include "DxLib.h"
#include "SceneManager.h"
#include "Game.h"
#include "Input.h"
#include "Font.h"
#include "Sound.h"
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

	Input input;		// ���͏�Ԃ��擾
	Font::Load();		// �t�H���g�̓ǂݍ���
	Sound::Load();		// �T�E���h�̓ǂݍ���
	Sound::ChangeVol();	// �T�E���h�̉��ʂ�ύX����

	// SceneManager�𐶐�
	std::shared_ptr<SceneManager> pScene = std::make_shared<SceneManager>();
	pScene->Init();

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

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667) {}

#ifdef _DEBUG
		if (input.IsTriggered("end"))
		{
			DxLib_End();
		}
#endif
	}

	Font::UnLoad();			 // �t�H���g�̉��
	Sound::UnLode();		 // �T�E���h�̉��

	DxLib_End();	// �c�w���C�u�����g�p�̏I������

	return 0;		// �\�t�g�̏I�� 
}