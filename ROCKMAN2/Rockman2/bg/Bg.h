#pragma once
#include "Vec2.h"
#include "Rect.h"
#include "Game.h"

class Player;
/// <summary>
/// 背景クラス
/// </summary>
class Bg
{
public:
	Bg();
	virtual ~Bg();

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	void DrawBg();
	// 操作説明の表示
	void DrawEx(int scrollX, int scrollY);

	// プレイヤーの位置からスクロール量を決定する
	int GetScrollX();
	int GetScrollY();

	// プレイヤーのポインタを設定
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

	// プレイヤーと当たっているか判定する
	bool IsColPlayer();
	// 指定した矩形と当たっているか判定する
	bool IsCollision(Rect rect, Rect& chipRect);

protected:
	// プレイヤーのポインタ
	Player* m_pPlayer;

	// 背景の表示位置
	Vec2 m_bgPos;
	// 背景の移動量
	float m_bgMove;

	// グラフィックに含まれるマップチップの数
	int m_graphChipNumX;
	int m_graphChipNumY;

	// 背景のグラフィック
	int m_bgHandle;	
	int m_bg2Handle;
	int m_bg3Handle;
	int m_bg4Handle;

	// マップチップのグラフィック
	int m_mapHandle;

	// 操作説明の画像
	int m_walkHandle;		// 移動
	int m_jumpHandle;		// ジャンプ
	int m_shotHandle;		// ショット
	int m_metalHandle;		// メタル
	int m_fireHandle;		// ファイア
	int m_lineHandle;		// 2号
	int m_menuHandle;		// メニュー
	int m_recoveryHandle;	// 回復アイテム

	// 説明画像のアニメーション
	int m_exAnimFrame;
	int m_exFireAnimFrame;

	// 画像サイズ
	struct Size
	{
		int width;
		int height;
	};
};