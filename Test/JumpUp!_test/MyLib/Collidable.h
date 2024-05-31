#pragma once
#include "Rigidbody.h"

class Rigidbody;
class Physics;

/// <summary>
/// 衝突できる物体の基底クラス
/// </summary>
class Collidable abstract
{
public:
	// 当たったものの判別を行う
	enum class Tag
	{
		Player,	// プレイヤー
		Floor,	// 床
		Ground	// 地面
	};

	Collidable(Tag tag);
	// 衝突した際の処理
	//virtual void OnCollide() = 0;

	Tag GetTag() const { return m_tag; }

protected:
	Rigidbody m_rigidbody;

private:
	Tag m_tag;

	// PhysicsがCollidableを自由に管理するためにフレンド化
	friend Physics;
};

