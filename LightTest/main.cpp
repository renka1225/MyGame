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

    int rabbitModel = MV1LoadModel("data/rabbit.mv1");
    int groundModel = MV1LoadModel("data/tile.mv1");

    // �Q�[�����[�v
    while (ProcessMessage() != -1)
    {
        // �J������]
        CameraRotate();

       // �`��
        DrawMaterial(groundModel);

        WaitKey();				// �L�[���͑҂�

        MV1DeleteModel(rabbitModel);
    }

	DxLib_End();			// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}