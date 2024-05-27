#pragma once
#include <list>

class Collidable;

/// <summary>
/// 衝突判定するオブジェクトを登録し、物理移動・衝突を通知するクラス
/// </summary>
class Physics
{
public:
	void Entry(Collidable* collidable);		// 衝突物の登録
	void Exit(Collidable* collidable);		// 衝突物の登録解除
	void Update();

private:
	// 直方体と直方体の当たり判定を行う
	bool HitCube();

private:
	// 登録されたCollidableのリスト
	std::list<Collidable*> m_collidables;
};

