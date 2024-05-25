#pragma once

class Rigidbody;
class Physics;

/// <summary>
/// 衝突できる物体の基底クラス
/// </summary>
class Collidable
{
public:
	// 当たったものの判別を行う
	enum class Tag
	{
		Player,	// プレイヤー
		Floor	// 床
	};

	Collidable(Tag tag);
	// 衝突した際の処理
	virtual void OnCollide() = 0;

	Tag GetTag() const { return m_tag; }

protected:
	Rigidbody m_rigidbody;

private:
	Tag m_tag;

	// PhysicsがCollidableを自由に管理するためにフレンド化
	friend Physics;
};

