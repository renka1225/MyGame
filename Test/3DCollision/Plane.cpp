#include "Plane.h"
#include <math.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
Plane::Plane():
    m_v3Vec1(VGet(0.0f, 0.8f, 0.0f)),
    m_v3Vec2(VGet(0.0f, 0.0f, 0.0f)),
    m_time(0),
    m_handle(-1)
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

    m_handle = LoadGraph("data/plane.png");
}


/// <summary>
/// �X�V
/// </summary>
void Plane::Update()
{
    m_time++;

    // �n�ʂ̌X�ΕύX
    // X����
    m_v3Vec1 = VGet(40.0f, 10.0f * sin(m_time * 0.5f * DX_PI_F / 100.0f), 0.0f);
    // Y����
    m_v3Vec2 = VGet(0.0f, 15.0f * sin(m_time * 0.5f * DX_PI_F / 120.0f), 50.0f);

    // ���ʂ𓮂���
    Vertex[0].pos = VAdd(VScale(m_v3Vec1, -1), m_v3Vec2);
    Vertex[1].pos = VAdd(m_v3Vec1, m_v3Vec2);
    Vertex[2].pos = VSub(VScale(m_v3Vec1, -1), m_v3Vec2);
    Vertex[3].pos = VSub(m_v3Vec1, m_v3Vec2);
}


/// <summary>
/// �`��
/// </summary>
void Plane::Draw()
{
	DrawPolygonIndexed3D(Vertex, 4, Index, 2, m_handle, true);
}
