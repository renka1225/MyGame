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

	// 現在の弾エネルギー数を取得する
	float GetMetalEnergy() const { return m_metalEnergy; }
	float GetFireEnergy() const { return m_fireEnergy; }
	float GetLineEnergy() const { return m_lineEnergy; }

	// ボタンを押して離すまでの時間を取得する
	int GetPressTime() const { return m_nowPressTime; }

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
	// ジャンプ中かどうか
	bool m_isJumpFlag;	// true:ジャンプ中
	// 初速度
	float m_velocity;

	// HP
	int m_hp;
	// 残機
	int m_life;

	// メタルの弾エネルギー数
	float m_metalEnergy;
	// ファイヤーの弾エネルギー数
	float m_fireEnergy;
	// アイテム2号の弾エネルギー数
	float m_lineEnergy;

	// ボタンの状態を取得する
	int m_keyState;
	// ボタンが長押しされた時間
	int m_pressTime;
	// ボタンを押して離すまでの時間
	int m_nowPressTime;
};

