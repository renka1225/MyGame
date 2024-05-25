#include "MyLib.h"
#include <cassert>

/// <summary>
/// 衝突物の登録
/// </summary>
/// <param name="collidable">衝突物</param>
void Physics::Entry(Collidable* collidable)
{
	// 衝突物を登録する
	bool found = std::find(m_collidables.begin(), m_collidables.end(), collidable) != m_collidables.end();
	if (!found)
	{
		// 要素を末尾に追加する
		m_collidables.emplace_back(collidable);
	}
	else // すでに登録されていたらエラー
	{
		assert(0 && "指定のcollidableは登録済です");
	}

}

/// <summary>
/// 衝突物の削除
/// </summary>
/// <param name="collidable">衝突物</param>
void Physics::Exit(Collidable* collidable)
{
	bool found = std::find(m_collidables.begin(), m_collidables.end(), collidable) != m_collidables.end();
	if (found)
	{
		m_collidables.remove(collidable);
	}
	else // 登録されていなかったらエラー
	{
		assert(0 && "指定のcollidableが登録されていません");
	}
}


/// <summary>
/// 更新
/// </summary>
void Physics::Update()
{
	// 衝突情報の更新と通知
	for (auto item : m_collidables)
	{
		// 移動
		auto pos = item->m_rigidbody.GetPos();
		auto nextPos = VAdd(pos, item->m_rigidbody.GetVelocity());
		
		//デバッグ表示
#ifdef _DEBUG
	
#endif

		item->m_rigidbody.SetPos(nextPos);

		// プレイヤーが障害物に当たったら
		if (HitCube())
		{
			// ポジションを補正する

			// 衝突通知を行う
			item->OnCollide();
		}
	}
}


/// <summary>
/// 直方体と直方体の衝突判定を行う
/// </summary>
bool Physics::HitCube()
{
	// 衝突しているか判定
	bool isHit = false;

	return isHit;

}
