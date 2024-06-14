#pragma once
#include "Collision3DBox.h"

class Player;
class DrawDebug;

/// <summary>
/// ステージの更新と描画を行うクラス
/// </summary>
class Stage
{
public:
	Stage();
	virtual ~Stage();
	void Init();
	void Update();
	void Draw(DrawDebug& drawDebug);
	// 当たり判定をして、補正した移動先のポジションを返す
	VECTOR CheckCollision(Player& player, const VECTOR& moveVector);

	// 指定した直方体と当たっているか判定
	bool IsCollision(Collision3DBox col3DBox, Collision3DBox& col3DMap);

	// 平面のX方向の傾斜を取得
	VECTOR GetV3Vec1() const { return m_v3Vec1; }
	// 平面のY方向の傾斜を取得
	VECTOR GetV3Vec2() const { return m_v3Vec2; }
	// ステージの位置を取得
	VECTOR GetStagePos() const { return m_stagePos; }
	// ステージモデルを取得
	int GetStageHandle() const { return m_stageHandle; }

private:
	// 床を作成する
	void CreateFloor();
	// 検出されたポリゴンが壁ポリゴンか床ポリゴンかを判断し、保存する
	void AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition);
	// 壁ポリゴンとの当たりをチェックし、プレイヤーの補正すべき移動ベクトルを返す
	VECTOR CheckHitWithWall(Player& player, const VECTOR& checkPosition);
	// 床ポリゴンとの当たりをチェックし、プレイヤーの補正すべき移動ベクトルを返す
	//VECTOR CheckHitWithFloor(Player& player, const VECTOR& checkPosition);

private:
	// 床の情報
	VECTOR m_floorPos;	// 床の位置
	int m_floorHandle;	// 床のモデル
	VECTOR m_v3Vec1;	// X方向の傾斜
	VECTOR m_v3Vec2;	// Y方向の傾斜
	// 頂点データ
	VERTEX3D m_vertex[4];
	WORD m_index[6];

	// ステージの情報
	// TODO: 後ほど複数にするのでvectorにする
	VECTOR m_stagePos;		// ステージの位置
	VECTOR m_stageScale;	// ステージの拡大率
	float m_angle;			// ステージの角度
	int m_stageHandle;		// ステージの3Dモデル

	// 壁の情報
	int m_wallNum;	// 壁ポリゴンと判断されたポリゴンの数
	int	m_floorNum;	// 床ポリゴンと判断されたポリゴンの数

	static const int MaxHitColl = 2048;			// 処理するコリジョンポリゴンの最大数
	MV1_COLL_RESULT_POLY* m_wall[MaxHitColl];		// 壁ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY* m_floor[MaxHitColl];	// 床ポリゴンと判断されたポリゴンの構造体のアドレスを保存しておくためのポインタ配列
};

