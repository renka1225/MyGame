#pragma once
#include <list>

class Collidable;

/// <summary>
/// 衝突判定するオブジェクトを登録し、物理移動・衝突を通知するクラス
/// </summary>
class Physics
{
public:
	// 衝突物の登録
	void Entry(Collidable* collidable);
	// 衝突物の登録解除
	void Exit(Collidable* collidable);

	void Update();

private:
	// 登録されたCollidableのリスト
	std::list<Collidable*> Collidables;
};

