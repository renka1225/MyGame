#include "DxLib.h"
#include "MyLib.h"
#include "Player.h"
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
/// �����蔻������āA�␳�����ړ���̃|�W�V������Ԃ�
/// </summary>
/// <param name="player">�v���C���[�̎Q��</param>
/// <param name="moveVector">�ړ���</param>
/// <returns></returns>
VECTOR Stage::CheckCollision(Player& player, const VECTOR& moveVector)
{
    VECTOR oldPos = player.GetPos();			    // �ړ��O�̍��W	
    VECTOR nextPos = VAdd(oldPos, moveVector);		// �ړ���̍��W

    // �v���C���[�̎��͂ɂ���X�e�[�W�|���S�����擾����
    auto hitDim = MV1CollCheck_Sphere(m_stageHandle, -1, oldPos, 32 + VSize(moveVector));

    // ���o���ꂽ�|���S�����ǃ|���S�������|���S�����𔻒f���ĕۑ�����
    AnalyzeWallAndFloor(hitDim, oldPos);

    // �ǃ|���S���Ƃ̓����蔻����`�F�b�N���A�v���C���[�̈ړ��x�N�g����␳����
    nextPos = CheckHitWithWall(player, nextPos);
    // ���|���S���Ƃ̓����蔻����`�F�b�N���A�v���C���[�̈ړ��x�N�g����␳����
    nextPos = CheckHitWithFloor(player, nextPos);

    return VECTOR();
}


/// <summary>
/// ���o���ꂽ�|���S�����ǃ|���S�������|���S�����𔻒f���A�ۑ�����
/// </summary>
/// <param name="hitDim">���ƃ��f���̓����蔻��</param>
/// <param name="checkPosition">�X�e�[�W�̈ʒu</param>
void Stage::AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition)
{
    // �ǃ|���S���Ə��|���S���̐�������������
    m_wallNum = 0;
    m_floorNum = 0;

    // ���o���ꂽ�|���S���̐������J��Ԃ�
    for (int i = 0; i < hitDim.HitNum; i++)
    {
        // XZ���ʂɐ������ǂ����̓|���S���̖@����Y������0�Ɍ���Ȃ��߂����ǂ����Ŕ��f����
        if (hitDim.Dim[i].Normal.y < 0.000001f && hitDim.Dim[i].Normal.y > -0.000001f)
        {
            // �ǃ|���S���Ɣ��f���ꂽ�ꍇ�ł��A�v���C���[��Y���W+1.0f��荂���|���S���̂ݓ����蔻����s��
            if (hitDim.Dim[i].Position[0].y > checkPosition.y + 1.0f ||
                hitDim.Dim[i].Position[1].y > checkPosition.y + 1.0f ||
                hitDim.Dim[i].Position[2].y > checkPosition.y + 1.0f)
            {
                // �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
                if (m_wallNum < MaxHitColl)
                {
                    // �|���S���̍\���̂̃A�h���X��ǃ|���S���|�C���^�z��ɕۑ�����
                    m_wall[m_wallNum] = &hitDim.Dim[i];
                    m_wallNum++;
                }
            }
        }
        else
        {
            // �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
            if (m_floorNum < MaxHitColl)
            {
                // �|���S���̍\���̂̃A�h���X�����|���S���|�C���^�z��ɕۑ�����
                m_floor[m_floorNum] = &hitDim.Dim[i];
                m_floorNum++;
            }
        }
    }
}


/// <summary>
/// �ǃ|���S���Ƃ̓����蔻����`�F�b�N
/// </summary>
/// <param name="player">�v���C���[�̎Q��</param>
/// <param name="checkPosition">�X�e�[�W�̈ʒu</param>
/// <returns>�␳����ړ��x�N�g��</returns>
VECTOR Stage::CheckHitWithWall(Player& player, const VECTOR& checkPosition)
{
    // �␳��̈ʒu
    VECTOR fixedPos = checkPosition;

    // �ǂ̐����Ȃ������牽�����Ȃ�
    if (m_wallNum == 0) return fixedPos;

    // �ǂ���̉����o���������s��
    for (int i = 0; i < HitTryNum; i++)
    {
        // ������\���̂���ǃ|���S����S�Č���
        bool isHitWall = false;
        for (int i = 0; i < m_wallNum; i++)
        {
            // i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
            auto poly = m_wall[i];

            // �ǂ̈ʒu
            VECTOR CapPos2 = VGet(0.0f, 70.0f, 0.0f);

            // �J�v�Z���ƎO�p�`�̓����蔻��
            if (HitCheck_Capsule_Triangle(fixedPos, VAdd(fixedPos, CapPos2), 20.0f, poly->Position[0], poly->Position[1], poly->Position[2]))
            {
                // �v���C���[��ǂ̖@�������Ɉړ�������
                // �ړ���̈ʒu��␳
                fixedPos = VAdd(fixedPos, VScale(poly->Normal, 5.0f));

                // �ړ������ǃ|���S���ƐڐG���Ă��邩�ǂ������肷��
                for (int j = 0; j < m_wallNum; j++)
                {
                    // �������Ă����烋�[�v�𔲂���
                    poly = m_wall[i];
                    if (HitCheck_Capsule_Triangle(fixedPos, VAdd(fixedPos, CapPos2), 20.0f, poly->Position[0], poly->Position[1], poly->Position[2]))
                    {
                        isHitWall = true;
                        break;
                    }
                }

                // �S�Ẵ|���S���Ɠ������Ă��Ȃ������烋�[�v�I��
                if (!isHitWall) break;
            }
        }

        // �S�Ă̕ǃ|���S���ƐڐG���Ȃ��Ȃ����烋�[�v���甲����
        if (!isHitWall) break;
    }

    return fixedPos;
}

VECTOR Stage::CheckHitWithFloor(Player& player, const VECTOR& checkPosition)
{
    return VECTOR();
}


/// <summary>
///  �v���C���[���Փ˂����Ƃ�
/// </summary>
//void Stage::OnCollide()
//{
//#ifdef _DEBUG
//    DrawString(0, 40, "�v���C���[����������", 0xffffff);
//#endif
//}
