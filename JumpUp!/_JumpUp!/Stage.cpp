#include "DxLib.h"
#include "MyLib.h"
#include "Player.h"
#include "Stage.h"
#include <math.h>

/// <summary>
/// コンストラクタ
/// </summary>
Stage::Stage():
    Collidable(Tag::Ground),
	m_floorPos(VGet(0.0f, 0.0f, 0.0f)),
	m_v3Vec1(VGet(0.0f, 0.8f, 0.0f)),
	m_v3Vec2(VGet(0.0f, 0.0f, 0.0f)),
    m_stagePos(VGet(0.0f, -10.0f, -30.0f)),
    m_stageScale(VGet(kFloorScaleX, kFloorScaleY, kFloorScaleZ))
{
    // ４頂点分のデータをセット
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

    // ２ポリゴン分のインデックスデータをセット
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
/// デストラクタ
/// </summary>
Stage::~Stage()
{
	MV1DeleteModel(m_floorHandle);
}

/// <summary>
/// 初期化
/// </summary>
void Stage::Init(std::shared_ptr<Physics> physics)
{
    // 自身の物理情報を登録する
    physics->Entry(this);
    m_rigidbody.Init();
    m_rigidbody.SetPos(m_stagePos);
    m_rigidbody.SetScale(m_stageScale);

	MV1SetPosition(m_stageHandle, m_stagePos);
	MV1SetScale(m_stageHandle, m_stageScale);
}


/// <summary>
/// 終了処理
/// </summary>
void Stage::Final(std::shared_ptr<Physics> physics)
{
    physics->Exit(this);
}

/// <summary>
/// 更新
/// </summary>
void Stage::Update()
{
    // 地面の傾斜変更
    // X方向
    m_v3Vec1 = VGet(40.0f, 10.0f * static_cast<float>(sin(0.5f * DX_PI_F / 2.0f)), 0.0f);
    // Y方向
    m_v3Vec2 = VGet(0.0f, 15.0f * static_cast<float>(sin(0.5f * DX_PI_F / 2.0f)), 50.0f);

    // 平面を動かす
    Vertex[0].pos = VAdd(VScale(m_v3Vec1, -1), m_v3Vec2);
    Vertex[1].pos = VAdd(m_v3Vec1, m_v3Vec2);
    Vertex[2].pos = VSub(VScale(m_v3Vec1, -1), m_v3Vec2);
    Vertex[3].pos = VSub(m_v3Vec1, m_v3Vec2);
}

/// <summary>
/// 描画
/// </summary>
void Stage::Draw(DrawDebug& drawDebug)
{
#ifdef _DEBUG	// デバッグ表示
    // 当たり判定描画
    drawDebug.DrawCubeCol(VGet(m_stagePos.x, m_stagePos.y + kCenterPosY, m_stagePos.z), kFloorScaleX, kFloorScaleY, kFloorScaleZ, 0xff0000);
#endif

	// 床を描画する
    DrawPolygonIndexed3D(Vertex, 4, Index, 2, m_floorHandle, true);

    // ステージ描画
    MV1DrawModel(m_stageHandle);
}


/// <summary>
/// 当たり判定をして、補正した移動先のポジションを返す
/// </summary>
/// <param name="player">プレイヤーの参照</param>
/// <param name="moveVector">移動量</param>
/// <returns></returns>
VECTOR Stage::CheckCollision(Player& player, const VECTOR& moveVector)
{
    VECTOR oldPos = player.GetPos();			    // 移動前の座標	
    VECTOR nextPos = VAdd(oldPos, moveVector);		// 移動後の座標

    // プレイヤーの周囲にあるステージポリゴンを取得する
    auto hitDim = MV1CollCheck_Sphere(m_stageHandle, -1, oldPos, 32 + VSize(moveVector));

    // 検出されたポリゴンが壁ポリゴンか床ポリゴンかを判断して保存する
    AnalyzeWallAndFloor(hitDim, oldPos);

    // 壁ポリゴンとの当たり判定をチェックし、プレイヤーの移動ベクトルを補正する
    nextPos = CheckHitWithWall(player, nextPos);
    // 床ポリゴンとの当たり判定をチェックし、プレイヤーの移動ベクトルを補正する
    nextPos = CheckHitWithFloor(player, nextPos);

    return VECTOR();
}


/// <summary>
/// 検出されたポリゴンが壁ポリゴンか床ポリゴンかを判断し、保存する
/// </summary>
/// <param name="hitDim">線とモデルの当たり判定</param>
/// <param name="checkPosition">ステージの位置</param>
void Stage::AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition)
{
    // 壁ポリゴンと床ポリゴンの数を初期化する
    m_wallNum = 0;
    m_floorNum = 0;

    // 検出されたポリゴンの数だけ繰り返す
    for (int i = 0; i < hitDim.HitNum; i++)
    {
        // XZ平面に垂直かどうかはポリゴンの法線のY成分が0に限りなく近いかどうかで判断する
        if (hitDim.Dim[i].Normal.y < 0.000001f && hitDim.Dim[i].Normal.y > -0.000001f)
        {
            // 壁ポリゴンと判断された場合でも、プレイヤーのY座標+1.0fより高いポリゴンのみ当たり判定を行う
            if (hitDim.Dim[i].Position[0].y > checkPosition.y + 1.0f ||
                hitDim.Dim[i].Position[1].y > checkPosition.y + 1.0f ||
                hitDim.Dim[i].Position[2].y > checkPosition.y + 1.0f)
            {
                // ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
                if (m_wallNum < MaxHitColl)
                {
                    // ポリゴンの構造体のアドレスを壁ポリゴンポインタ配列に保存する
                    m_wall[m_wallNum] = &hitDim.Dim[i];
                    m_wallNum++;
                }
            }
        }
        else
        {
            // ポリゴンの数が列挙できる限界数に達していなかったらポリゴンを配列に追加
            if (m_floorNum < MaxHitColl)
            {
                // ポリゴンの構造体のアドレスを床ポリゴンポインタ配列に保存する
                m_floor[m_floorNum] = &hitDim.Dim[i];
                m_floorNum++;
            }
        }
    }
}


/// <summary>
/// 壁ポリゴンとの当たり判定をチェック
/// </summary>
/// <param name="player">プレイヤーの参照</param>
/// <param name="checkPosition">ステージの位置</param>
/// <returns>補正する移動ベクトル</returns>
VECTOR Stage::CheckHitWithWall(Player& player, const VECTOR& checkPosition)
{
    // 補正後の位置
    VECTOR fixedPos = checkPosition;

    // 壁の数がなかったら何もしない
    if (m_wallNum == 0) return fixedPos;

    // 壁からの押し出し処理を行う
    for (int i = 0; i < HitTryNum; i++)
    {
        // 当たる可能性のある壁ポリゴンを全て見る
        bool isHitWall = false;
        for (int i = 0; i < m_wallNum; i++)
        {
            // i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
            auto poly = m_wall[i];

            // 壁の位置
            VECTOR CapPos2 = VGet(0.0f, 70.0f, 0.0f);

            // カプセルと三角形の当たり判定
            if (HitCheck_Capsule_Triangle(fixedPos, VAdd(fixedPos, CapPos2), 20.0f, poly->Position[0], poly->Position[1], poly->Position[2]))
            {
                // プレイヤーを壁の法線方向に移動させる
                // 移動後の位置を補正
                fixedPos = VAdd(fixedPos, VScale(poly->Normal, 5.0f));

                // 移動した壁ポリゴンと接触しているかどうか判定する
                for (int j = 0; j < m_wallNum; j++)
                {
                    // 当たっていたらループを抜ける
                    poly = m_wall[i];
                    if (HitCheck_Capsule_Triangle(fixedPos, VAdd(fixedPos, CapPos2), 20.0f, poly->Position[0], poly->Position[1], poly->Position[2]))
                    {
                        isHitWall = true;
                        break;
                    }
                }

                // 全てのポリゴンと当たっていなかったらループ終了
                if (!isHitWall) break;
            }
        }

        // 全ての壁ポリゴンと接触しなくなったらループから抜ける
        if (!isHitWall) break;
    }

    return fixedPos;
}

VECTOR Stage::CheckHitWithFloor(Player& player, const VECTOR& checkPosition)
{
    return VECTOR();
}


/// <summary>
///  プレイヤーが衝突したとき
/// </summary>
//void Stage::OnCollide()
//{
//#ifdef _DEBUG
//    DrawString(0, 40, "プレイヤーが当たった", 0xffffff);
//#endif
//}
