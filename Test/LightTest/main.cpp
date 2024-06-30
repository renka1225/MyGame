#include "DxLib.h"

// �s����g�����J������]
void CameraRotate()
{
    // �J������]
    float Rotate = 0.0f;
    MATRIX Matrix;

    // ���E�L�[�ŃJ�����̉�]�l��ύX
    if (CheckHitKey(KEY_INPUT_LEFT) == 1)
    {
        Rotate -= DX_PI_F / 60.0f;
    }
    if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
    {
        Rotate += DX_PI_F / 60.0f;
    }

    // ��]�l���g�p���Ăx���̉�]�s����쐬
    Matrix = MGetRotY(Rotate);

    // ��]�s����r���[�s��Ƃ��ăZ�b�g
    SetCameraViewMatrix(Matrix);
}

// �}�e���A���`��
void DrawMaterial(int groundModel)
{
    // �}�e���A���̎��Ȕ����F���Â��F�ɂ���
    MATERIALPARAM Material;
    Material.Diffuse = GetColorF(0.8f, 0.0f, 0.0f, 0.0f);   // �g�U���F
    Material.Specular = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);  // �����F
    Material.Ambient = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);   // ���ˌ��F
    Material.Emissive = GetColorF(0.9f, 0.0f, 0.0f, 0.0f);  // ���Ȕ����F
    Material.Power = 20.0f;                                 // �X�y�L�����̋���
    SetMaterialParam(Material);

    Material.Emissive = GetColorF(0.0f, 0.2f, 0.9f, 0.0f);  // ���Ȕ����F
    SetMaterialParam(Material);
    // �f�t�H���g�̐ݒ�łR�c��ԏ�ɋ���`�悷��
    DrawSphere3D(VGet(320.0f, 200.0f, 0.0f), 40.0f, 32, GetColor(128, 0, 0), GetColor(255, 255, 255), true);


    Material.Specular = GetColorF(0.0f, 0.8f, 0.0f, 1.0f);  // �����F
    Material.Emissive = GetColorF(0.9f, 0.4f, 0.0f, 0.0f);  // ���Ȕ����F
    Material.Power = 20.0f;                                 // �X�y�L�����̋���
    SetMaterialParam(Material);
    // �f�t�H���g�̐ݒ�łR�c��ԏ�ɋ���`�悷��
    DrawSphere3D(VGet(480.0f, 200.0f, 0.0f), 40.0f, 32, GetColor(0, 0, 0), GetColor(255, 255, 255), true);

    // 3D���f���\��
    MV1SetPosition(groundModel, VGet(160.0f, 200.0f, 0.0f));
    MV1SetDifColorScale(groundModel, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
    MV1DrawModel(groundModel);
}

// �v���O������ WinMain ����n�܂�܂�
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	if (DxLib_Init() == -1)		// �c�w���C�u��������������
//	{
//		return -1;			// �G���[���N�����璼���ɏI��
//	}
//
//    // �y�o�b�t�@��L���ɂ���
//    SetUseZBuffer3D(TRUE);
//    // �y�o�b�t�@�ւ̏������݂�L���ɂ���
//    SetWriteZBuffer3D(TRUE);
//
//    int rabbitModel = MV1LoadModel("data/rabbit.mv1");
//    int groundModel = MV1LoadModel("data/tile.mv1");
//
//    // �Q�[�����[�v
//    while (ProcessMessage() != -1)
//    {
//        // �J������]
//        CameraRotate();
//
//       // �`��
//        DrawMaterial(groundModel);
//
//        WaitKey();				// �L�[���͑҂�
//
//        MV1DeleteModel(rabbitModel);
//    }
//
//	DxLib_End();			// �c�w���C�u�����g�p�̏I������
//
//	return 0;				// �\�t�g�̏I�� 
//}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int ModelHandle;
    float Range, Atten0, Atten1, Atten2;

    // �c�w���C�u�����̏�����
    if (DxLib_Init() < 0)
    {
        // �G���[�����������璼���ɏI��
        return -1;
    }

    // ���f���̓ǂݍ���
    ModelHandle = MV1LoadModel("data/rabbit.mv1");

    // �`���𗠉�ʂɂ���
    SetDrawScreen(DX_SCREEN_BACK);

    // �e�p�����[�^��������
    Range = 2000.0f;
    Atten0 = 0.0f;
    Atten1 = 0.0006f;
    Atten2 = 0.0f;

    // �d�r�b�L�[��������邩�E�C���h�E��������܂Ń��[�v
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // ��ʂ��N���A
        ClearDrawScreen();

        // �c�b�L�[�Ń��C�g�̉e���͈͂�ύX
        if (CheckHitKey(KEY_INPUT_D) == 1)
        {
            Range += 20.0f;
        }
        if (CheckHitKey(KEY_INPUT_C) == 1)
        {
            Range -= 20.0f;
        }

        // �e�u�L�[�Ń��C�g�̋��������p�����[�^�O�̒l��ύX
        if (CheckHitKey(KEY_INPUT_F) == 1)
        {
            Atten0 += 0.001f;
        }
        if (CheckHitKey(KEY_INPUT_V) == 1)
        {
            Atten0 -= 0.001f;
        }

        // �f�a�L�[�Ń��C�g�̋��������p�����[�^�P�̒l��ύX
        if (CheckHitKey(KEY_INPUT_G) == 1)
        {
            Atten1 += 0.00001f;
        }
        if (CheckHitKey(KEY_INPUT_B) == 1)
        {
            Atten1 -= 0.00001f;
        }

        // �g�m�L�[�Ń��C�g�̋��������p�����[�^�Q�̒l��ύX
        if (CheckHitKey(KEY_INPUT_H) == 1)
        {
            Atten2 += 0.0000001f;
        }
        if (CheckHitKey(KEY_INPUT_N) == 1)
        {
            Atten2 -= 0.0000001f;
        }

        // �e�������̒l��␳
        if (Range < 0.0f) Range = 0.0f;

        // ���������p�����[�^�̒l��␳
        if (Atten0 < 0.0f) Atten0 = 0.0f;
        if (Atten1 < 0.0f) Atten1 = 0.0f;
        if (Atten2 < 0.0f) Atten2 = 0.0f;

        // ���f���̏��Ƀ|�C���g���C�g��ݒ�
        ChangeLightTypePoint(
            VGet(320.0f, 1000.0f, 200.0f),
            Range,
            Atten0,
            Atten1,
            Atten2);

        // ���f�����J�����̉f��ʒu�Ɉړ�
        MV1SetPosition(ModelHandle, VGet(320.0f, 240.0f, 200.0f));

        // ���f����`��
        MV1DrawModel(ModelHandle);

        // �p�����[�^�̓��e����ʂɕ\��
        DrawFormatString(0, 0, GetColor(255, 255, 255), "Key:D.C  Range  %f", Range);
        DrawFormatString(0, 16, GetColor(255, 255, 255), "Key:F.V  Atten0 %f", Atten0);
        DrawFormatString(0, 32, GetColor(255, 255, 255), "Key:G.B  Atten1 %f", Atten1);
        DrawFormatString(0, 48, GetColor(255, 255, 255), "Key:H.N  Atten2 %f / 100.0f", Atten2 * 100.0f);

        // ����ʂ̓��e��\��ʂɔ��f����
        ScreenFlip();
    }

    // ���f���n���h���̍폜
    MV1DeleteModel(ModelHandle);

    // �c�w���C�u�����̌�n��
    DxLib_End();

    // �\�t�g�̏I��
    return 0;
}