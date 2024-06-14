#include "DxLib.h"
#include "Stage.h"
#include "Player.h"
#include "DrawDebug.h"
#include <cmath>

// 定数
namespace
{
    // マップサイズ
    constexpr float kWidth = 100.0f;  // 横幅
    constexpr float kHeight = 3.0f;   // 縦幅
    constexpr float kDepth = 100.0f;   // 奥行き

    // 当たり判定
    constexpr float kDefaultSize = 200.0f;	// 周囲のポリゴン検出に使用する球の初期サイズ
    constexpr float kHitWidth = 50.0f;	    // 当たり判定カプセルの半径
    constexpr float kHitHeight = 100.0f;	// 当たり判定カプセルの高さ
    constexpr int kHitTryNum = 16;		    // 壁押し出し処理の最大試行回数
    constexpr float kHitSlideLength = 5.0f;	// 一度の壁押し出し処理でスライドさせる距離
}


/// <summary>
/// コンストラクタ
/// </summary>
Stage::Stage():
    m_wallNum(0),
    m_floorNum(0)
{
	m_stageHandle = MV1LoadModel("data/model/stage.mv1");
    MV1SetScale(m_stageHandle, VGet(kWidth, kHeight, kDepth));

    // モデル全体のコリジョン情報のセットアップ
    MV1SetupCollInfo(m_stageHandle, -1);
}


/// <summary>
/// デストラクタ
/// </summary>
Stage::~Stage()
{
    MV1DeleteModel(m_stageHandle);
}


/// <summary>
/// 描画
/// </summary>
void Stage::Draw()
{
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

    // 検出されたポリゴンが壁ポリゴンか床ポリゴンか判別し、保存する
    // MEMO:壁ポリゴン(XZ平面に垂直なポリゴン)、床ポリゴン(XZ平面に垂直でないポリゴン)
    AnalyzeWallAndFloor(hitDim, oldPos);

    // 壁ポリゴンとの当たり判定をチェックし、プレイヤーの移動ベクトルを補正する
    nextPos = CheckHitWithWall(player, nextPos);
    // 床ポリゴンとの当たり判定をチェックし、プレイヤーの移動ベクトルを補正する
    nextPos = CheckHitWithFloor(player, nextPos);

    // 検出したプレイヤーの周囲のポリゴン情報の後始末をする
    MV1CollResultPolyDimTerminate(hitDim);

    return nextPos;
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
        // XZ平面に垂直かどうか
        // MEMO:垂直かどうかはポリゴンの法線のY成分が0に限りなく近いかどうかで判断する
        bool isVertical = hitDim.Dim[i].Normal.y < 0.000001f && hitDim.Dim[i].Normal.y > -0.000001f;
        
        // XZ平面に垂直な場合(壁ポリゴンと判断された場合)
        if (isVertical)
        {
            // 壁ポリゴンと判断された場合でも、プレイヤーのY座標+1.0fより高いポリゴンのみ当たり判定を行う
            if (hitDim.Dim[i].Position[0].y > checkPosition.y + 1.0f ||
                hitDim.Dim[i].Position[1].y > checkPosition.y + 1.0f ||
                hitDim.Dim[i].Position[2].y > checkPosition.y + 1.0f)
            {
                // ポリゴンの数が列挙できる限界数に達していない場合、ポリゴンを配列に追加する
                if (m_wallNum < MaxHitColl)
                {
                    // ポリゴンの構造体のアドレスを壁ポリゴンポインタ配列に保存する
                    m_wall[m_wallNum] = &hitDim.Dim[i];
                    m_wallNum++;
                }
            }
        }
        // XZ平面に垂直でない場合
        else
        {
            // ポリゴンの数が列挙できる限界数に達していない場合、ポリゴンを配列に追加
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
/// 壁ポリゴンとの当たりをチェックする
/// </summary>
/// <param name="player">プレイヤー参照</param>
/// <param name="checkPosition">移動後の座標</param>
/// <returns>補正すべきベクトル</returns>
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
///  床ポリゴンとの当たりをチェックする
/// </summary>
/// <param name="player">プレイヤー参照</param>
/// <param name="checkPosition">移動後の座標</param>
/// <returns>補正すべきベクトル</returns>
VECTOR Stage::CheckHitWithFloor(Player& player, const VECTOR& checkPosition)
{
    VECTOR fixedPos = checkPosition;

    // 床の数がなかったら何もしない
    if (m_floorNum == 0) return fixedPos;

    // ジャンプ中かつ上昇中の場合
    if (player.GetState() == Player::State::kJump && player.GetJumpPower() > 0.0f)
    {
        // 天井に頭をぶつける処理を行う
        bool isHitRoof = false;
        float minY = 0.0f;

        // 床ポリゴンの数だけ繰り返す
        for (int i = 0; i < m_floorNum; i++)
        {
            auto poly = m_floor[i]; // i番目の床ポリゴンのアドレス

            // 足先から頭までの高さの間でポリゴンと接触しているか判定する
            HITRESULT_LINE lineResult;  // 線分とポリゴンとの当たり判定の結果を代入する
            VECTOR fixedEndPos = VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f)); // プレイヤーの終点
            lineResult = HitCheck_Line_Triangle(fixedPos, fixedEndPos, poly->Position[0], poly->Position[1], poly->Position[2]);

            // 接触していたら何もしない
            if (lineResult.HitFlag)
            {
                // 既にポリゴンに当たっていて、今まで検出した天井ポリゴンより高い場合は何もしない
                if (!(isHitRoof && minY < lineResult.Position.y))
                {
                    isHitRoof = true;
                    // 接触したY座標を保存する
                    minY = lineResult.Position.y;
                }
            }
        }

        // 接触したポリゴンがあった場合
        if (isHitRoof)
        {
            // プレイヤーのY座標を更新
            fixedPos.y = minY - kHitHeight;
            player.OnHitRoof();
        }
    }
    // 下降中またはジャンプ中でない場合の処理
    else
    {
        bool isHitFloor = false;
        float maxY = 0.0f;

        for (int i = 0; i < m_floorNum; i++)
        {
            auto poly = m_floor[i]; // i番目の床ポリゴンのアドレス

            // ジャンプ中かどうか
            HITRESULT_LINE lineResult;  // 線分とポリゴンとの当たり判定の結果を代入する構造体
            if (player.GetState() == Player::State::kJump)
            {
                // ジャンプ中の場合は頭の先から足先より少し低い位置の間で当たっているかを判定
                lineResult = HitCheck_Line_Triangle(VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f)), VAdd(fixedPos, VGet(0.0f, -1.0f, 0.0f)), poly->Position[0], poly->Position[1], poly->Position[2]);
            }
            else
            {
                // 走っている場合は頭の先からそこそこ低い位置の間で当たっているかを判定(傾斜で落下状態に移行してしまわない為)
                lineResult = HitCheck_Line_Triangle(VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f)), VAdd(fixedPos, VGet(0.0f, -40.0f, 0.0f)), poly->Position[0], poly->Position[1], poly->Position[2]);
            }

            // 既に当たったポリゴンがあり、且つ今まで検出した床ポリゴンより低い場合は何もしない
            if (lineResult.HitFlag)
            {
                if (!(isHitFloor && maxY > lineResult.Position.y))
                {
                    // 接触したＹ座標を保存する
                    isHitFloor = true;
                    maxY = lineResult.Position.y;
                }
            }
        }

        // 床ポリゴンに当たった
        if (isHitFloor == true)
        {
            // 接触したポリゴンで一番高いＹ座標をプレイヤーのＹ座標にする
            fixedPos.y = maxY;

            // 床に当たった処理を行う
            player.OnHitFloor();
        }
        else
        {
            // 床コリジョンに当たっておらず、ジャンプ状態でない場合は落下状態にする
            player.OnFall();
        }
    }

    return fixedPos;
}