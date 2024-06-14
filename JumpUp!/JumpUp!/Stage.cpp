#include "DxLib.h"
#include "Stage.h"
#include "Player.h"
#include "DrawDebug.h"
#include <cmath>

// 定数
namespace
{
	// 床の拡大率
	constexpr float kFloorScaleX = 30.0f;
	constexpr float kFloorScaleY = 10.0f;
	constexpr float kFloorScaleZ = 20.0f;

    // 当たり判定
    static constexpr float kCenterPosY = 5.0f;	// 地面の中心点を調整

    static constexpr float kDefaultSize = 200.0f;	// 周囲のポリゴン検出に使用する球の初期サイズ
    static constexpr float kHitWidth = 50.0f;	    // 当たり判定カプセルの半径
    static constexpr float kHitHeight = 100.0f;	    // 当たり判定カプセルの高さ
    static constexpr int kHitTryNum = 16;		    // 壁押し出し処理の最大試行回数
    static constexpr float kHitSlideLength = 5.0f;	// 一度の壁押し出し処理でスライドさせる距離
}


/// <summary>
/// コンストラクタ
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

    // モデル全体のコリジョン情報のセットアップ
    MV1SetupCollInfo(m_stageHandle, -1);
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
void Stage::Init()
{
    // 床を作成
	CreateFloor();

    // ステージを作成
    MV1SetPosition(m_stageHandle, m_stagePos);
    MV1SetScale(m_stageHandle, m_stageScale);
}


/// <summary>
/// 更新
/// </summary>
void Stage::Update()
{
    // 平面を動かす
    m_vertex[0].pos = VAdd(VScale(m_v3Vec1, -1), m_v3Vec2);
    m_vertex[1].pos = VAdd(m_v3Vec1, m_v3Vec2);
    m_vertex[2].pos = VSub(VScale(m_v3Vec1, -1), m_v3Vec2);
    m_vertex[3].pos = VSub(m_v3Vec1, m_v3Vec2);
}


/// <summary>
/// 描画
/// </summary>
/// <param name="drawDebug"></param>
void Stage::Draw(DrawDebug& drawDebug)
{
#ifdef _DEBUG	// デバッグ表示
    // 当たり判定描画
    drawDebug.DrawCubeCol(m_floorHandle, m_angle, 0xff0000);
#endif

    // 床を描画する
    DrawPolygonIndexed3D(m_vertex, 4, m_index, 2, m_floorHandle, true);

    // ステージ描画
    MV1DrawModel(m_stageHandle);
}


/// <summary>
/// 当たり判定をして、補正した移動先のポジションを返す
/// </summary>
/// <param name="player">プレイヤー参照</param>
/// <param name="moveVector">プレイヤーの移動量</param>
/// <returns>移動後の座標</returns>
VECTOR Stage::CheckCollision(Player& player, const VECTOR& moveVector)
{
    VECTOR oldPos = player.GetPos();			// 移動前の座標	
    VECTOR nextPos = VAdd(oldPos, moveVector);	// 移動後の座標

    // プレイヤーの周囲にあるステージポリゴンを取得する
    auto hitDim = MV1CollCheck_Sphere(m_stageHandle, -1, oldPos, kDefaultSize + VSize(moveVector));

    // 壁ポリゴンとの当たり判定をチェックし、プレイヤーの移動ベクトルを補正する
    nextPos = CheckHitWithWall(player, nextPos);
    // 床ポリゴンとの当たり判定をチェックし、プレイヤーの移動ベクトルを補正する
   // nextPos = CheckHitWithFloor(player, nextPos);

    // 検出したプレイヤーの周囲のポリゴン情報の後始末をする
    MV1CollResultPolyDimTerminate(hitDim);

    return nextPos;
}


/// <summary>
/// 床を作成
/// </summary>
void Stage::CreateFloor()
{
    // ４頂点分のデータをセット
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

    // ２ポリゴン分のインデックスデータをセット
    m_index[0] = 0;
    m_index[1] = 1;
    m_index[2] = 2;
    m_index[3] = 3;
    m_index[4] = 2;
    m_index[5] = 1;

    // X方向
    m_v3Vec1 = VGet(40.0f, 10.0f * static_cast<float>(sin(0.5f * DX_PI_F / 2.0f)), 0.0f);
    // Y方向
    m_v3Vec2 = VGet(0.0f, 15.0f * static_cast<float>(sin(0.5f * DX_PI_F / 2.0f)), 50.0f);
}


/// <summary>
/// 検出されたポリゴンが壁ポリゴンか床ポリゴンかを判断し、保存する
/// </summary>
/// <param name="hitDim">線とモデルの当たり判定</param>
/// <param name="checkPosition">移動後の座標</param>
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
/// 壁ポリゴンとの当たりをチェックし、補正すべき移動ベクトルを返す
/// </summary>
/// <param name="player">プレイヤー参照</param>
/// <param name="checkPosition">移動後の座標</param>
/// <returns>補正するベクトル</returns>
VECTOR Stage::CheckHitWithWall(Player& player, const VECTOR& checkPosition)
{
    // 補正後の位置
    VECTOR fixedPos = checkPosition;

    // 壁の数がなかったら何もしない
    if (m_wallNum == 0) return fixedPos;

    // 壁からの押し出し処理を行う
    for (int i = 0; i < kHitTryNum; i++)
    {
        // 当たる可能性のある壁ポリゴンを全て見る
        bool isHitWall = false;
        for (int i = 0; i < m_wallNum; i++)
        {
            // i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
            auto poly = m_wall[i];

            // 壁の位置
            VECTOR CapPos2 = VGet(0.0f, kHitHeight, 0.0f);

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


/// <summary>
/// 床ポリゴンとの当たりをチェックし、補正すべき移動ベクトルを返す
/// </summary>
/// <param name="player"></param>
/// <param name="checkPosition"></param>
/// <returns></returns>
//VECTOR Stage::CheckHitWithFloor(Player& player, const VECTOR& checkPosition)
//{
//    VECTOR fixedPos = checkPosition;
//    // 床の数がなかったら何もしない
//    if (m_floorNum == 0) return fixedPos;
//
//    // ジャンプ中かつ上昇中の場合
//    if (player.GetState() == Player::State::kJump && player.GetMove().y > 0.0f)
//    {
//        // 天井に頭をぶつける処理を行う
//        bool isHitRoof = false;
//        float minY = 0.0f;
//
//        // 床ポリゴンの数だけ繰り返す
//        for (int i = 0; i < m_floorNum; i++)
//        {
//            auto poly = m_floor[i]; // i番目の床ポリゴンのアドレス
//
//            // 足先から頭までの高さの間でポリゴンと接触しているか判定する
//            HITRESULT_LINE lineResult;  // 線分とポリゴンとの当たり判定の結果を代入する構造体
//            lineResult = HitCheck_Line_Triangle(fixedPos, VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f)), poly->Position[0], poly->Position[1], poly->Position[2]);
//
//            // 接触していたら何もしない
//            if (lineResult.HitFlag)
//            {
//                // 既にポリゴンに当たっていて、今まで検出した天井ポリゴンより高い場合は何もしない
//                if (!(isHitRoof && minY < lineResult.Position.y))
//                {
//                    // ポリゴンに当たったフラグを立てる
//                    isHitRoof = true;
//                    // 接触したY座標を保存する
//                    minY = lineResult.Position.y;
//                }
//            }
//        }
//
//        // 接触したポリゴンがあった場合
//        if (isHitRoof)
//        {
//            // 接触した場合、プレイヤーのY座標を更新
//            fixedPos.y = minY - kHitHeight;
//            player.OnHitRoof();
//        }
//    }
//    // 下降中またはジャンプ中でない場合の処理
//    else
//    {
//        bool isHitFloor = false;
//        float maxY = 0.0f;
//
//        for (int i = 0; i < m_floorNum; i++)
//        {
//            auto poly = m_floor[i]; // i番目の床ポリゴンのアドレス
//
//            // ジャンプ中かどうか
//            HITRESULT_LINE lineResult;  // 線分とポリゴンとの当たり判定の結果を代入する構造体
//            if (player.GetState() == Player::State::Jump)
//            {
//                // ジャンプ中の場合は頭の先から足先より少し低い位置の間で当たっているかを判定
//                lineResult = HitCheck_Line_Triangle(VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f)), VAdd(fixedPos, VGet(0.0f, -1.0f, 0.0f)), poly->Position[0], poly->Position[1], poly->Position[2]);
//            }
//            else
//            {
//                // 走っている場合は頭の先からそこそこ低い位置の間で当たっているかを判定(傾斜で落下状態に移行してしまわない為)
//                lineResult = HitCheck_Line_Triangle(VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f)), VAdd(fixedPos, VGet(0.0f, -40.0f, 0.0f)), poly->Position[0], poly->Position[1], poly->Position[2]);
//            }
//
//            // 既に当たったポリゴンがあり、且つ今まで検出した床ポリゴンより低い場合は何もしない
//            if (lineResult.HitFlag)
//            {
//                if (!(isHitFloor && maxY > lineResult.Position.y))
//                {
//                    // 接触したＹ座標を保存する
//                    isHitFloor = true;
//                    maxY = lineResult.Position.y;
//                }
//            }
//        }
//
//        // 床ポリゴンに当たった
//        if (isHitFloor == true)
//        {
//            // 接触したポリゴンで一番高いＹ座標をプレイヤーのＹ座標にする
//            fixedPos.y = maxY;
//
//            // 床に当たった時
//            player.OnHitFloor();
//        }
//        else
//        {
//            // 床コリジョンに当たっていなくて且つジャンプ状態ではなかった場合は落下状態
//            player.OnFall();
//        }
//    }
//
//    return fixedPos;
//}


/// <summary>
/// プレイヤーと当たっているか判定
/// </summary>
/// <returns>当たったか</returns>
bool Stage::IsCollision(Collision3DBox col3DBox, Collision3DBox& col3DMap)
{
    // 相対ベクトルを求める
    VECTOR v3SubAbs = VSub(col3DBox.GetCenter(), col3DBox.m_centerPos);
    v3SubAbs = VGet(abs(v3SubAbs.x), abs(v3SubAbs.y), abs(v3SubAbs.z));

    // 衝突距離を求める
    // 衝突距離はそれぞれの対応した辺の長さを足して2で割ったもの
    float col3DSizeX = col3DBox.m_right - col3DBox.m_left;
    float col3DSizeY = col3DBox.m_top - col3DBox.m_bottom;
    float col3DSizeZ = col3DBox.m_back - col3DBox.m_front;

    VECTOR v3AddScale = VScale(VAdd(VGet(col3DSizeX, col3DSizeY, col3DSizeZ), VGet(5.0f, 0.0f, 0.0f)), 0.5f);
    // TODO;当たり判定の範囲を広げる(仮実装)
    v3AddScale = VAdd(v3AddScale, VGet(0.0f, 20.0f, 0.0f));

    // 各成分の当たり判定
    bool isXHit = v3SubAbs.x < v3AddScale.x;
    bool isYHit = v3SubAbs.y < v3AddScale.y;
    bool isZHit = v3SubAbs.z < v3AddScale.z;

    if (isXHit && isYHit && isZHit) return true;

    return false;
}
