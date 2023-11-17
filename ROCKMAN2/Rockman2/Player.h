#pragma once
#include "Vec2.h"

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

	int m_handle; // グラフィックのハンドル
	Vec2 m_pos;	  // 表示位置
};

