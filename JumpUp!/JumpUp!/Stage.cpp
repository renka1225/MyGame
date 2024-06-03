#include "DxLib.h"
#include "Stage.h"
#include "DrawDebug.h"
#include <cmath>

// �萔
namespace
{
	// ���̊g�嗦
	constexpr float kFloorScaleX = 30.0f;
	constexpr float kFloorScaleY = 10.0f;
	constexpr float kFloorScaleZ = 20.0f;

    // �����蔻��
    static constexpr float kCenterPosY = 5.0f;	// �n�ʂ̒��S�_�𒲐�
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
Stage::Stage():
	m_floorPos(VGet(0.0f, 0.0f, 0.0f)),
	m_v3Vec1(VGet(0.0f, 0.8f, 0.0f)),
	m_v3Vec2(VGet(0.0f, 0.0f, 0.0f)),
	m_stagePos(VGet(0.0f, 3.0f, -30.0f)),
	m_stageScale(VGet(kFloorScaleX, kFloorScaleY, kFloorScaleZ)),
    m_angle(0.0f)
{
	m_stageHandle = MV1LoadModel("data/model/stage.mv1");
    m_floorHandle = LoadGraph("data/plane.png");
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
void Stage::Init()
{
    // �����쐬
	CreateFloor();

    // �X�e�[�W���쐬
    MV1SetPosition(m_stageHandle, m_stagePos);
    MV1SetScale(m_stageHandle, m_stageScale);
}


/// <summary>
/// �X�V
/// </summary>
void Stage::Update()
{
    // ���ʂ𓮂���
    m_vertex[0].pos = VAdd(VScale(m_v3Vec1, -1), m_v3Vec2);
    m_vertex[1].pos = VAdd(m_v3Vec1, m_v3Vec2);
    m_vertex[2].pos = VSub(VScale(m_v3Vec1, -1), m_v3Vec2);
    m_vertex[3].pos = VSub(m_v3Vec1, m_v3Vec2);
}


/// <summary>
/// �`��
/// </summary>
/// <param name="drawDebug"></param>
void Stage::Draw(DrawDebug& drawDebug)
{
#ifdef _DEBUG	// �f�o�b�O�\��
    // �����蔻��`��
    drawDebug.DrawCubeCol(m_floorHandle, m_angle, 0xff0000);
#endif

    // ����`�悷��
    DrawPolygonIndexed3D(m_vertex, 4, m_index, 2, m_floorHandle, true);

    // �X�e�[�W�`��
    MV1DrawModel(m_stageHandle);
}


/// <summary>
/// �����쐬
/// </summary>
void Stage::CreateFloor()
{
    // �S���_���̃f�[�^���Z�b�g
    m_vertex[0].pos = VGet(-30.0f, 0.0f, 40.0f);
    m_vertex[0].norm = VGet(0.0f, 0.0f, -1.0f);

    m_vertex[1].pos = VGet(30.0f, 20.0f, 40.0f);
    m_vertex[1].norm = VGet(0.0f, 0.0f, -1.0f);

    m_vertex[2].pos = VGet(-30.0f, 0.0f, -40.0f);
    m_vertex[2].norm = VGet(0.0f, 0.0f, -1.0f);

    m_vertex[3].pos = VGet(30.0f, 20.0f, -40.0f);
    m_vertex[3].norm = VGet(0.0f, 0.0f, -1.0f);

    for (int i = 0; i < 4; i++)
    {
        m_vertex[i].dif = GetColorU8(255, 255, 255, 255);
        m_vertex[i].spc = GetColorU8(0, 0, 0, 0);
        m_vertex[i].u = 0.0f;
        m_vertex[i].v = 0.0f;
        m_vertex[i].su = 0.0f;
        m_vertex[i].sv = 0.0f;
    }

    // �Q�|���S�����̃C���f�b�N�X�f�[�^���Z�b�g
    m_index[0] = 0;
    m_index[1] = 1;
    m_index[2] = 2;
    m_index[3] = 3;
    m_index[4] = 2;
    m_index[5] = 1;

    // X����
    m_v3Vec1 = VGet(40.0f, 10.0f * static_cast<float>(sin(0.5f * DX_PI_F / 2.0f)), 0.0f);
    // Y����
    m_v3Vec2 = VGet(0.0f, 15.0f * static_cast<float>(sin(0.5f * DX_PI_F / 2.0f)), 50.0f);
}
