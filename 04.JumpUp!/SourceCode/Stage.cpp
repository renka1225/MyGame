#include "DxLib.h"
#include "Stage.h"
#include "Player.h"
#include "Game.h"
#include "DrawDebug.h"
#include <cmath>

// 定数
namespace
{
    constexpr float kStageScale = 0.1f;                // ステージサイズ
    constexpr float kFragScale = 30.0f;                // フラッグのサイズ
    const VECTOR kFragPos = VGet(0.0f, 856.0f, 0.0f);  // フラッグの位置
    constexpr int kBgColor = 0x2d6676;                 // 背景色

    // 当たり判定
    constexpr float kDefaultSize = 100.0f;	// 周囲のポリゴン検出に使用する球の初期サイズ
    constexpr float kHitWidth = 10.0f;	    // 当たり判定カプセルの半径
    constexpr float kHitHeight = 20.0f;	    // 当たり判定カプセルの高さ
    constexpr float kHitBottom = -1.0f;	    // 当たり判定カプセルの位置
    constexpr float kHitBottom2 = -40.0f;	// 当たり判定カプセルの位置
    constexpr int kHitTryNum = 16;		    // 壁押し出し処理の最大試行回数
    constexpr float kHitSlideLength = 1.0f;	// 一度の壁押し出し処理でスライドさせる距離
}


/// <summary>
/// コンストラクタ
/// </summary>
Stage::Stage():
    m_wallNum(0),
    m_floorNum(0)
{
	m_stageHandle = MV1LoadModel("data/Model/stage.mv1");
    m_flagHandle = MV1LoadModel("data/Model/flag.mv1");

    MV1SetScale(m_stageHandle, VGet(kStageScale, kStageScale, kStageScale));
    MV1SetScale(m_flagHandle, VGet(kFragScale, kFragScale, kFragScale));
    MV1SetPosition(m_flagHandle, kFragPos);

    // モデル全体のコリジョン情報のセットアップ
    MV1SetupCollInfo(m_stageHandle, -1);
    MV1SetupCollInfo(m_flagHandle, -1);
}


/// <summary>
/// デストラクタ
/// </summary>
Stage::~Stage()
{
    MV1DeleteModel(m_stageHandle);
    MV1DeleteModel(m_flagHandle);
}


/// <summary>
/// 描画
/// </summary>
void Stage::Draw()
{
    // 背景描画
    DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, kBgColor, true);

    // ステージ描画
    MV1DrawModel(m_stageHandle);
    MV1DrawModel(m_flagHandle);
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
/// ゴールフラッグとの当たり判定をチェックする
/// </summary>
/// <param name="player">プレイヤー参照</param>
/// <param name="checkPosition">プレイヤーの移動量</param>
/// <returns>フラッグに当たったかどうか</returns>
bool Stage::CheckHitFlag(Player& player, const VECTOR& checkPosition)
{
    // プレイヤーの周囲にあるポリゴンを取得する
    auto hitDim = MV1CollCheck_Capsule(m_flagHandle, -1, player.GetPos(), checkPosition, kHitHeight);

    if (hitDim.HitNum >= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
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

            // プレイヤーの終点
            VECTOR fixedEndPos = VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f));
            // プレイヤーが壁に当たっているか
            bool isHit = HitCheck_Capsule_Triangle(fixedPos, fixedEndPos, kHitWidth, poly->Position[0], poly->Position[1], poly->Position[2]);

            // プレイヤーと当たっている場合
            if (isHit)
            {
                // プレイヤーを壁の法線方向に移動させる
                fixedPos = VAdd(fixedPos, VScale(poly->Normal, kHitSlideLength));

                // 移動した壁ポリゴンと接触しているかどうか判定する
                for (int j = 0; j < m_wallNum; j++)
                {
                    // 当たっていたらループを抜ける
                    poly = m_wall[j];
                    if (isHit)
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

            HITRESULT_LINE lineResult;  // 線分とポリゴンとの当たり判定の結果を代入する構造体
            VECTOR topPos = VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f));       // プレイヤーの頭の先の位置
            VECTOR bottomPos = VAdd(fixedPos, VGet(0.0f, kHitBottom, 0.0f));    // プレイヤーの足元より少し低い位置
            VECTOR bottomPos2 = VAdd(fixedPos, VGet(0.0f, kHitBottom2, 0.0f));  // プレイヤーの足元よりさらに低い位置

            // ジャンプ中の場合
            if (player.GetState() == Player::State::kJump)
            {
                // 頭の先から足先より少し低い位置の間で当たっているかを判定する
                lineResult = HitCheck_Line_Triangle(topPos, bottomPos, poly->Position[0], poly->Position[1], poly->Position[2]);
            }
            // 移動中の場合
            else
            {
                // 頭の先からそこそこ低い位置の間で当たっているかを判定する
                lineResult = HitCheck_Line_Triangle(topPos, bottomPos2, poly->Position[0], poly->Position[1], poly->Position[2]);
            }

            // 既に当たったポリゴンがあり、検出した床ポリゴンより低い場合何もしない
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

        // 床ポリゴンに当たった場合
        if (isHitFloor)
        {
            // プレイヤーを床に接触させる
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