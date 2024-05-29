#include "DxLib.h"
#include "MyLib.h"
#include "Stage.h"
#include <math.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
Stage::Stage():
    Collidable(Tag::Ground),
	m_floorPos(VGet(0.0f, 0.0f, 0.0f)),
	m_v3Vec1(VGet(0.0f, 0.8f, 0.0f)),
	m_v3Vec2(VGet(0.0f, 0.0f, 0.0f)),
    m_stagePos(VGet(0.0f, -10.0f, -30.0f)),
    m_stageScale(VGet(kFloorScaleX, kFloorScaleY, kFloorScaleZ))
{
    // �S���_���̃f�[�^���Z�b�g
    Vertex[0].pos = VGet(-30.0f, 0.0f, 40.0f);
    Vertex[0].norm = VGet(0.0f, 0.0f, -1.0f);

    Vertex[1].pos = VGet(30.0f, 20.0f, 40.0f);
    Vertex[1].norm = VGet(0.0f, 0.0f, -1.0f);

    Vertex[2].pos = VGet(-30.0f, 0.0f, -40.0f);
    Vertex[2].norm = VGet(0.0f, 0.0f, -1.0f);

    Vertex[3].pos = VGet(30.0f, 20.0f, -40.0f);
    Vertex[3].norm = VGet(0.0f, 0.0f, -1.0f);

    for (int i = 0; i < 4; i++)
    {
        Vertex[i].dif = GetColorU8(255, 255, 255, 255);
        Vertex[i].spc = GetColorU8(0, 0, 0, 0);
        Vertex[i].u = 0.0f;
        Vertex[i].v = 0.0f;
        Vertex[i].su = 0.0f;
        Vertex[i].sv = 0.0f;
    }

    // �Q�|���S�����̃C���f�b�N�X�f�[�^���Z�b�g
    Index[0] = 0;
    Index[1] = 1;
    Index[2] = 2;
    Index[3] = 3;
    Index[4] = 2;
    Index[5] = 1;

    m_floorHandle = LoadGraph("data/plane.png");
    m_stageHandle = MV1LoadModel("data/model/stage.mv1");
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Stage::~Stage()
{
	MV1DeleteModel(m_floorHandle);
}

/// <summary>
/// ������
/// </summary>
void Stage::Init(std::shared_ptr<Physics> physics)
{
    // ���g�̕�������o�^����
    physics->Entry(this);
    m_rigidbody.Init();
    m_rigidbody.SetPos(m_stagePos);
    m_rigidbody.SetScale(m_stageScale);

	MV1SetPosition(m_stageHandle, m_stagePos);
	MV1SetScale(m_stageHandle, m_stageScale);
}


/// <summary>
/// �I������
/// </summary>
void Stage::Final(std::shared_ptr<Physics> physics)
{
    physics->Exit(this);
}

/// <summary>
/// �X�V
/// </summary>
void Stage::Update()
{
    // �n�ʂ̌X�ΕύX
    // X����
    m_v3Vec1 = VGet(40.0f, 10.0f * static_cast<float>(sin(0.5f * DX_PI_F / 2.0f)), 0.0f);
    // Y����
    m_v3Vec2 = VGet(0.0f, 15.0f * static_cast<float>(sin(0.5f * DX_PI_F / 2.0f)), 50.0f);

    // ���ʂ𓮂���
    Vertex[0].pos = VAdd(VScale(m_v3Vec1, -1), m_v3Vec2);
    Vertex[1].pos = VAdd(m_v3Vec1, m_v3Vec2);
    Vertex[2].pos = VSub(VScale(m_v3Vec1, -1), m_v3Vec2);
    Vertex[3].pos = VSub(m_v3Vec1, m_v3Vec2);
}

/// <summary>
/// �`��
/// </summary>
void Stage::Draw(DrawDebug& drawDebug)
{
#ifdef _DEBUG	// �f�o�b�O�\��
    // �����蔻��`��
    drawDebug.DrawCubeCol(VGet(m_stagePos.x, m_stagePos.y + kCenterPosY, m_stagePos.z), kFloorScaleX, kFloorScaleY, kFloorScaleZ, 0xff0000);
#endif

	// ����`�悷��
    DrawPolygonIndexed3D(Vertex, 4, Index, 2, m_floorHandle, true);

    // �X�e�[�W�`��
    MV1DrawModel(m_stageHandle);
}


/// <summary>
///  �v���C���[���Փ˂����Ƃ�
/// </summary>
void Stage::OnCollide()
{
#ifdef _DEBUG
    DrawString(0, 40, "�v���C���[����������", 0xffffff);
#endif
}
