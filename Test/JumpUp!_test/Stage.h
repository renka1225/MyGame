#pragma once
#include "Collidable.h"
#include <memory>

class Player;
class Collidable;
class DrawDebug;

/// <summary>
/// ステージの描画と更新を行うクラス
/// </summary>
class Stage : public Collidable
{
public:
	Stage();
	virtual ~Stage();
	void Init(std::shared_ptr<Physics> physics);
	void Final(std::shared_ptr<Physics> physics);
	void Update();
	void Draw(DrawDebug& drawDebug);

	// 当たり判定をして、補正後のポジションを返す
	VECTOR CheckCollision(Player& player, const VECTOR& moveVector);

	// 平面のX方向の傾斜を取得
	VECTOR GetV3Vec1() const { return m_v3Vec1; }
	// 平面のY方向の傾斜を取得
	VECTOR GetV3Vec2() const { return m_v3Vec2; }
	// ステージの位置を取得
	VECTOR GetStagePos() const { return m_stagePos; }
	// ステージモデルを取得
	int GetStageHandle() const { return m_stageHandle; }

private:
	// 検出されたポリゴンが壁ポリゴンか床ポリゴンかを判断し、保存する
	void AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition);
	// 壁ポリゴンとの当たりをチェックし、プレイヤーの補正すべき移動ベクトルを返す
	VECTOR CheckHitWithWall(Player& player, const VECTOR& checkPosition);
	// 床ポリゴンとの当たりをチェックし、プレイヤーの補正すべき移動ベクトルを返す
	VECTOR CheckHitWithFloor(Player& player, const VECTOR& checkPosition);

private:
	// 床の情報
	VECTOR m_floorPos;	// 床の位置
	int m_floorHandle;	// 床のモデル

	// 頂点データ
	VERTEX3D Vertex[4];
	WORD Index[6];

	// X方向の傾斜
	VECTOR m_v3Vec1;
	// Y方向の傾斜
	VECTOR m_v3Vec2;

	// ステージの情報
	VECTOR m_stagePos;		// ステージの位置
	VECTOR m_stageScale;	// ステージの拡大率
	int m_stageHandle;		// ステージの3Dモデル

	// 壁の情報
	int m_wallNum;	// 壁ポリゴンと判断されたポリゴンの数
	int	m_floorNum;	// 床ポリゴンと判断されたポリゴンの数

	static const int MaxHitColl = 2048;			// 処理するコリジョンポリゴンの最大数
	MV1_COLL_RESULT_POLY* m_wall[MaxHitColl];		// 壁ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY* m_floor[MaxHitColl];	// 床ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列

private:	// 定数
	// 床の拡大率
	static constexpr float kFloorScaleX = 30.0f;
	static constexpr float kFloorScaleY = 10.0f;
	static constexpr float kFloorScaleZ = 20.0f;
	static constexpr float kHitWidth = 200.0f;	// 当たり判定カプセルの半径
	static constexpr float kHitHeight = 700.0f;	// 当たり判定カプセルの高さ

	// 当たり判定
	static constexpr float kCenterPosY = 5.0f;	// 地面の中心点を調整
	static constexpr int kHitTryNum = 16;		// 壁押し出し処理の最大試行回数
};

