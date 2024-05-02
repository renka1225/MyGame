#include "DxLib.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

    // �y�o�b�t�@��L���ɂ���
    SetUseZBuffer3D(TRUE);

    // �y�o�b�t�@�ւ̏������݂�L���ɂ���
    SetWriteZBuffer3D(TRUE);

    // �}�e���A���̎��Ȕ����F���Â��F�ɂ���
    MATERIALPARAM Material;
    Material.Diffuse = GetColorF(0.0f, 0.0f, 0.0f, 1.0f);   // �g�U���F
    Material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);  // �����F
    Material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);   // ���ˌ��F
    Material.Emissive = GetColorF(0.5f, 0.0f, 0.0f, 0.0f);  // ���Ȕ����F
    Material.Power = 20.0f;                                 // �X�y�L�����̋���
    SetMaterialParam(Material);
    // �f�t�H���g�̐ݒ�łR�c��ԏ�ɋ���`�悷��
    DrawSphere3D(VGet(160.0f, 200.0f, 0.0f), 40.0f, 32, GetColor(128, 0, 0), GetColor(255, 255, 255), true);


    Material.Emissive = GetColorF(0.0f, 0.2f, 0.9f, 0.0f);  // ���Ȕ����F
    SetMaterialParam(Material);
    // �f�t�H���g�̐ݒ�łR�c��ԏ�ɋ���`�悷��
    DrawSphere3D(VGet(320.0f, 200.0f, 0.0f), 40.0f, 32, GetColor(128, 0, 0), GetColor(255, 255, 255), true);


    Material.Specular = GetColorF(0.0f, 0.8f, 0.0f, 1.0f);  // �����F
    Material.Emissive = GetColorF(0.0f, 0.4f, 0.0f, 0.0f);  // ���Ȕ����F
    Material.Power = 10.0f;                                 // �X�y�L�����̋���
    SetMaterialParam(Material);
    // �f�t�H���g�̐ݒ�łR�c��ԏ�ɋ���`�悷��
    DrawSphere3D(VGet(480.0f, 200.0f, 0.0f), 40.0f, 32, GetColor(0, 0, 0), GetColor(255, 255, 255), true);


	WaitKey();				// �L�[���͑҂�

	DxLib_End();			// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}