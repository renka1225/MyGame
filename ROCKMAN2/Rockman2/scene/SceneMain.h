#pragma once
#include <vector>
#include "Vec2.h"

class Player;
class Bg;
class ShotBase;
class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void End();
	void Update();
	void Draw();

	// ショットの追加
	// 登録できなかった場合はfalseを返す、内部でpShotを解放する
	bool AddShot(ShotBase* pShot);


private:
	// グラフィックのハンドル
	int m_bgHandle;			// 背景
	int m_playerHandle;		// プレイヤー

	// 背景
	Bg* m_pBg;
	// プレイヤー
	Player* m_pPlayer;
	// ショット
	std::vector<ShotBase*> m_pShot;

};

