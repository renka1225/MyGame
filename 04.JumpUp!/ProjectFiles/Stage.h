#pragma once

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
	void Draw();
	// 当たり判定をして、補正した移動先のポジションを返す
	VECTOR CheckCollision(Player& player, const VECTOR& moveVector);
	// ゴールフラッグとの当たり判定をチェックする
	bool CheckHitFlag(Player& player, const VECTOR& checkPosition);

	// ステージモデルを取得
	int GetStageHandle() const { return m_stageHandle; }

private:
	// 検出されたポリゴンが壁ポリゴンか床ポリゴンかを判断する
	void AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition);
	// 壁ポリゴンとの当たりをチェックする
	VECTOR CheckHitWithWall(Player& player, const VECTOR& checkPosition);
	// 床ポリゴンとの当たりをチェックする
	VECTOR CheckHitWithFloor(Player& player, const VECTOR& checkPosition);

private:
	// ステージ情報
	int m_wallNum;		// 壁ポリゴンの数
	int	m_floorNum;		// 床ポリゴンの数
	int m_stageHandle;	// ステージの3Dモデル
	int m_flagHandle;	// フラッグの3Dモデル

	static const int MaxHitColl = 2048;			// 処理するコリジョンポリゴンの最大数
	MV1_COLL_RESULT_POLY* m_wall[MaxHitColl];	// 壁ポリゴンの構造体のアドレスを保存しておくためのポインタ配列
	MV1_COLL_RESULT_POLY* m_floor[MaxHitColl];	// 床ポリゴンの構造体のアドレスを保存しておくためのポインタ配列
};

