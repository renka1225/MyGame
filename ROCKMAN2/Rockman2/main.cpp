#include "DxLib.h"
#include "Game.h"
#include "SceneManager.h"

// �V���b�g�̐�
#define SHOT	3

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);

	// ��ʃT�C�Y�̕ύX
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	int shotX[SHOT], shotY[SHOT]; // �e�̈ʒu
	int shotFlag[SHOT];				// �e�����݂��邩
	int m_shotHandle = LoadGraph("data/image/shotBuster.png"); // �e�̉摜

	// �e����ʏ�ɑ��݂��Ă��邩�ێ�����ϐ��Ɂw���݂��Ă��Ȃ��x���Ӗ�����false�������Ă���
	for (int i = 0; i < SHOT; i++)
	{
		shotFlag[i] = false;
	}
	// �V���b�g�{�^�����O�̃t���[���ŉ����ꂽ���ǂ�����ۑ�����ϐ���false(�����ꂢ�Ȃ�)����
	bool prevShotFlag = false;

	// Scene�̊J�n
	SceneManager* pScene = new SceneManager;
	pScene->Init();

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// �Q�[���̏���
 		pScene->Update();

		// �e����
		if (KEY_INPUT_0)
		{
			// �O�t���[���ŃV���b�g�{�^���������������ۑ�����Ă���ϐ���false��������e�𔭎�
			if (prevShotFlag == false)
			{
				for (int i = 0; i < 3; i++)
				{
					// �ei����ʏ�ɂłĂ��Ȃ��ꍇ�͂��̒e����ʂɏo��
					if (shotFlag[i] == false)
					{
						// �ei�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̒��S�ɂ���
						shotX[i] = 32;
						shotY[i] = 32;

						// �ei�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
						shotFlag[i] = true;

						break;
					}
				}
			}
			else
			{
				// �V���b�g�{�^����������Ă��Ȃ������ꍇ��
				// �O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ���false(������Ă��Ȃ�)����
				prevShotFlag = false;
			}
		}

		for (int i = 0; i < SHOT; i++)
		{
			if (shotFlag[i] == true)
			{
				// �ei���P�U�h�b�g��Ɉړ�������
				shotY[i] -= 8;

				// ��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ���false(���݂��Ȃ�)��������
				if (shotY[i] < -80)
				{
					shotFlag[i] = false;
				}

				DrawGraph(shotX[i], shotY[i], m_shotHandle, FALSE);
			}
		}

		pScene->Draw();

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		// esc�L�[�ŃQ�[���I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60�ɌŒ肷��
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66�~���b(16667�}�C�N���b)�o�߂���܂ő҂�
		}
	}
	pScene->End();

	// �������̉��
	delete pScene;
	pScene = nullptr;

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}