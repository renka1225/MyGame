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
	// プレイヤーの現在座標を取得する
	Vec2 GetPos() const { return m_pos; }

private:
	SceneMain* m_pMain;

	// 表示位置
	Vec2 m_pos;
	// 当たり判定用の矩形
	Rect m_colRect;
	// グラフィックのハンドル
	int m_handle;
	// ジャンプのフレーム数
	int m_jumpFrame;
	// ジャンプ中かどうか
	bool m_isJumpFlag;
	// HP
	int m_hp;
	// 残機
	int m_life;
};

