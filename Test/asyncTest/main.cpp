#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int m_handle;

    // �c�w���C�u�����̏�����
    if (DxLib_Init() < 0) return -1;

    // �񓯊��ǂݍ��ݐݒ�ɕύX
    SetUseASyncLoadFlag(true);

    // ���f����ǂݍ���
    m_handle = MV1LoadModel("data/city.mv1");

    // �����ǂݍ��ݐݒ�ɕύX
    SetUseASyncLoadFlag(false);

    // �`���𗠉�ʂɂ���
    SetDrawScreen(DX_SCREEN_BACK);

    while (ProcessMessage() == 0 && CheckHitKeyAll() == 0)
    {
        // ��ʂ̃N���A
        ClearDrawScreen();

        // CheckHandleASyncLoad(int Handle)  �n���h���̔񓯊��ǂݍ��݂��������Ă��邩�ǂ������擾����
        if (CheckHandleASyncLoad(m_handle))
        {
            DrawString(0, 40, "�ǂݍ��ݒ�\n", 0xffffff);
        }
        else
        {
            DrawString(0, 40, "�ǂݍ��ݏI��\n", 0xffffff);
            MV1SetScale(m_handle, VGet(10.0f, 10.0f, 10.0f));
            MV1DrawModel(m_handle);
        }

        // �񓯊��ǂݍ��݂̐���`��
        DrawFormatString(0, 0, GetColor(255, 255, 255), "�񓯊��ǂݍ��݂̐� %d", GetASyncLoadNum());

        // ����ʂ̓��e��\��ʂɔ��f
        ScreenFlip();

        //WaitKey();
    }

    // �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜����
    MV1DeleteModel(m_handle);

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}