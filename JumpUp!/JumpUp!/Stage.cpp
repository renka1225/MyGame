#include "DxLib.h"
#include "Stage.h"
#include "Player.h"
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

    static constexpr float kDefaultSize = 200.0f;	// ���͂̃|���S�����o�Ɏg�p���鋅�̏����T�C�Y
    static constexpr float kHitWidth = 50.0f;	    // �����蔻��J�v�Z���̔��a
    static constexpr float kHitHeight = 100.0f;	    // �����蔻��J�v�Z���̍���
    static constexpr int kHitTryNum = 16;		    // �ǉ����o�������̍ő厎�s��
    static constexpr float kHitSlideLength = 5.0f;	// ��x�̕ǉ����o�������ŃX���C�h�����鋗��
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
Stage::Stage():
	m_floorPos(VGet(0.0f, 0.0f, 0.0f)),
	m_v3Vec1(VGet(0.0f, 0.8f, 0.0f)),
	m_v3Vec2(VGet(0.0f, 0.0f, 0.0f)),
	m_stagePos(VGet(0.0f, 0.0f, -30.0f)),
	m_stageScale(VGet(kFloorScaleX, kFloorScaleY, kFloorScaleZ)),
    m_angle(0.0f),
    m_wallNum(0),
    m_floorNum(0)
{
	m_stageHandle = MV1LoadModel("data/model/stage.mv1");
    m_floorHandle = LoadGraph("data/plane.png");

    // ���f���S�̂̃R���W�������̃Z�b�g�A�b�v
    MV1SetupCollInfo(m_stageHandle, -1);
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
/// �����蔻������āA�␳�����ړ���̃|�W�V������Ԃ�
/// </summary>
/// <param name="player">�v���C���[�Q��</param>
/// <param name="moveVector">�v���C���[�̈ړ���</param>
/// <returns>�ړ���̍��W</returns>
VECTOR Stage::CheckCollision(Player& player, const VECTOR& moveVector)
{
    VECTOR oldPos = player.GetPos();			// �ړ��O�̍��W	
    VECTOR nextPos = VAdd(oldPos, moveVector);	// �ړ���̍��W

    // �v���C���[�̎��͂ɂ���X�e�[�W�|���S�����擾����
    auto hitDim = MV1CollCheck_Sphere(m_stageHandle, -1, oldPos, kDefaultSize + VSize(moveVector));

    // �ǃ|���S���Ƃ̓����蔻����`�F�b�N���A�v���C���[�̈ړ��x�N�g����␳����
    nextPos = CheckHitWithWall(player, nextPos);
    // ���|���S���Ƃ̓����蔻����`�F�b�N���A�v���C���[�̈ړ��x�N�g����␳����
   // nextPos = CheckHitWithFloor(player, nextPos);

    // ���o�����v���C���[�̎��͂̃|���S�����̌�n��������
    MV1CollResultPolyDimTerminate(hitDim);

    return nextPos;
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


/// <summary>
/// ���o���ꂽ�|���S�����ǃ|���S�������|���S�����𔻒f���A�ۑ�����
/// </summary>
/// <param name="hitDim">���ƃ��f���̓����蔻��</param>
/// <param name="checkPosition">�ړ���̍��W</param>
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
/// �ǃ|���S���Ƃ̓�������`�F�b�N���A�␳���ׂ��ړ��x�N�g����Ԃ�
/// </summary>
/// <param name="player">�v���C���[�Q��</param>
/// <param name="checkPosition">�ړ���̍��W</param>
/// <returns>�␳����x�N�g��</returns>
VECTOR Stage::CheckHitWithWall(Player& player, const VECTOR& checkPosition)
{
    // �␳��̈ʒu
    VECTOR fixedPos = checkPosition;

    // �ǂ̐����Ȃ������牽�����Ȃ�
    if (m_wallNum == 0) return fixedPos;

    // �ǂ���̉����o���������s��
    for (int i = 0; i < kHitTryNum; i++)
    {
        // ������\���̂���ǃ|���S����S�Č���
        bool isHitWall = false;
        for (int i = 0; i < m_wallNum; i++)
        {
            // i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
            auto poly = m_wall[i];

            // �ǂ̈ʒu
            VECTOR CapPos2 = VGet(0.0f, kHitHeight, 0.0f);

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


/// <summary>
/// ���|���S���Ƃ̓�������`�F�b�N���A�␳���ׂ��ړ��x�N�g����Ԃ�
/// </summary>
/// <param name="player"></param>
/// <param name="checkPosition"></param>
/// <returns></returns>
//VECTOR Stage::CheckHitWithFloor(Player& player, const VECTOR& checkPosition)
//{
//    VECTOR fixedPos = checkPosition;
//    // ���̐����Ȃ������牽�����Ȃ�
//    if (m_floorNum == 0) return fixedPos;
//
//    // �W�����v�����㏸���̏ꍇ
//    if (player.GetState() == Player::State::kJump && player.GetMove().y > 0.0f)
//    {
//        // �V��ɓ����Ԃ��鏈�����s��
//        bool isHitRoof = false;
//        float minY = 0.0f;
//
//        // ���|���S���̐������J��Ԃ�
//        for (int i = 0; i < m_floorNum; i++)
//        {
//            auto poly = m_floor[i]; // i�Ԗڂ̏��|���S���̃A�h���X
//
//            // ���悩�瓪�܂ł̍����̊ԂŃ|���S���ƐڐG���Ă��邩���肷��
//            HITRESULT_LINE lineResult;  // �����ƃ|���S���Ƃ̓����蔻��̌��ʂ�������\����
//            lineResult = HitCheck_Line_Triangle(fixedPos, VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f)), poly->Position[0], poly->Position[1], poly->Position[2]);
//
//            // �ڐG���Ă����牽�����Ȃ�
//            if (lineResult.HitFlag)
//            {
//                // ���Ƀ|���S���ɓ������Ă��āA���܂Ō��o�����V��|���S����荂���ꍇ�͉������Ȃ�
//                if (!(isHitRoof && minY < lineResult.Position.y))
//                {
//                    // �|���S���ɓ��������t���O�𗧂Ă�
//                    isHitRoof = true;
//                    // �ڐG����Y���W��ۑ�����
//                    minY = lineResult.Position.y;
//                }
//            }
//        }
//
//        // �ڐG�����|���S�����������ꍇ
//        if (isHitRoof)
//        {
//            // �ڐG�����ꍇ�A�v���C���[��Y���W���X�V
//            fixedPos.y = minY - kHitHeight;
//            player.OnHitRoof();
//        }
//    }
//    // ���~���܂��̓W�����v���łȂ��ꍇ�̏���
//    else
//    {
//        bool isHitFloor = false;
//        float maxY = 0.0f;
//
//        for (int i = 0; i < m_floorNum; i++)
//        {
//            auto poly = m_floor[i]; // i�Ԗڂ̏��|���S���̃A�h���X
//
//            // �W�����v�����ǂ���
//            HITRESULT_LINE lineResult;  // �����ƃ|���S���Ƃ̓����蔻��̌��ʂ�������\����
//            if (player.GetState() == Player::State::Jump)
//            {
//                // �W�����v���̏ꍇ�͓��̐悩�瑫���菭���Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�
//                lineResult = HitCheck_Line_Triangle(VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f)), VAdd(fixedPos, VGet(0.0f, -1.0f, 0.0f)), poly->Position[0], poly->Position[1], poly->Position[2]);
//            }
//            else
//            {
//                // �����Ă���ꍇ�͓��̐悩�炻�������Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�(�X�΂ŗ�����ԂɈڍs���Ă��܂�Ȃ���)
//                lineResult = HitCheck_Line_Triangle(VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f)), VAdd(fixedPos, VGet(0.0f, -40.0f, 0.0f)), poly->Position[0], poly->Position[1], poly->Position[2]);
//            }
//
//            // ���ɓ��������|���S��������A�����܂Ō��o�������|���S�����Ⴂ�ꍇ�͉������Ȃ�
//            if (lineResult.HitFlag)
//            {
//                if (!(isHitFloor && maxY > lineResult.Position.y))
//                {
//                    // �ڐG�����x���W��ۑ�����
//                    isHitFloor = true;
//                    maxY = lineResult.Position.y;
//                }
//            }
//        }
//
//        // ���|���S���ɓ�������
//        if (isHitFloor == true)
//        {
//            // �ڐG�����|���S���ň�ԍ����x���W���v���C���[�̂x���W�ɂ���
//            fixedPos.y = maxY;
//
//            // ���ɓ���������
//            player.OnHitFloor();
//        }
//        else
//        {
//            // ���R���W�����ɓ������Ă��Ȃ��Ċ��W�����v��Ԃł͂Ȃ������ꍇ�͗������
//            player.OnFall();
//        }
//    }
//
//    return fixedPos;
//}


/// <summary>
/// �v���C���[�Ɠ������Ă��邩����
/// </summary>
/// <returns>����������</returns>
bool Stage::IsCollision(Collision3DBox col3DBox, Collision3DBox& col3DMap)
{
    // ���΃x�N�g�������߂�
    VECTOR v3SubAbs = VSub(col3DBox.GetCenter(), col3DBox.m_centerPos);
    v3SubAbs = VGet(abs(v3SubAbs.x), abs(v3SubAbs.y), abs(v3SubAbs.z));

    // �Փˋ��������߂�
    // �Փˋ����͂��ꂼ��̑Ή������ӂ̒����𑫂���2�Ŋ���������
    float col3DSizeX = col3DBox.m_right - col3DBox.m_left;
    float col3DSizeY = col3DBox.m_top - col3DBox.m_bottom;
    float col3DSizeZ = col3DBox.m_back - col3DBox.m_front;

    VECTOR v3AddScale = VScale(VAdd(VGet(col3DSizeX, col3DSizeY, col3DSizeZ), VGet(5.0f, 0.0f, 0.0f)), 0.5f);
    // TODO;�����蔻��͈̔͂��L����(������)
    v3AddScale = VAdd(v3AddScale, VGet(0.0f, 20.0f, 0.0f));

    // �e�����̓����蔻��
    bool isXHit = v3SubAbs.x < v3AddScale.x;
    bool isYHit = v3SubAbs.y < v3AddScale.y;
    bool isZHit = v3SubAbs.z < v3AddScale.z;

    if (isXHit && isYHit && isZHit) return true;

    return false;
}
