#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class Player
{
public:
	Player(SceneMain* pMain);
	~Player();

	void Init();
	void Update();
	void Draw();

	// メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }
	// プレイヤーの現在の向きを取得する
	bool GetDir() const { return m_isRight; }
	// プレイヤーの現在座標を取得する
	Vec2 GetPos() const { return m_pos; }
	// プレイヤーの当たり判定を取得する
	Rect GetColRect() const { return m_colRect; }

private:
	SceneMain* m_pMain;

	// 表示位置
	Vec2 m_pos;
	// 当たり判定用の矩形
	Rect m_colRect;

	// グラフィックのハンドル
	int m_handle;
	// 向いている方向
	bool m_isRight;
	// ジャンプのフレーム数
	int m_jumpFrame;
	// ジャンプ中かどうか
	bool m_isJumpFlag;
	// HP
	int m_hp;
	// 残機
	int m_life;
};

