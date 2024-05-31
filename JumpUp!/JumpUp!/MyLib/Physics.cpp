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
	}

	// 衝突通知、ポジション補正を行う
	bool doCheck = true;
	int checkCount = 0;	// チェック回数
	while (doCheck)
	{
		doCheck = false;
		checkCount++;

		// 2重ループで全オブジェクトの当たり判定
		for (auto player : m_collidables)
		{
			for (auto ground : m_collidables)
			{
				if (player != ground)
				{
					// プレイヤーが障害物に当たったら
					if (HitCube(player, ground))
					{
						printfDx("当たった\n");
						auto pos1 = player->m_rigidbody.GetPos();
						auto pos2 = player->m_rigidbody.GetPos();

						// ポジションを補正する
						player->m_rigidbody.SetPos(VSub(pos1, pos2));

						// 衝突通知を行う
						//player->OnCollide();
						//ground->OnCollide();

						if (ground->GetTag() == Collidable::Tag::Ground)
						{
							player->m_rigidbody.SetPos(VAdd(player->m_rigidbody.GetPos(), VSub(player->m_rigidbody.GetPos(), ground->m_rigidbody.GetPos())));
						}
					}
				}
			}
		}
	}
}


/// <summary>
/// 直方体と直方体の衝突判定を行う
/// </summary>
bool Physics::HitCube(Collidable* player, Collidable* ground)
{
	// TODO:ここら辺のGetが上手く行ってないので調整
	/*プレイヤーと地面の当たり判定*/
	// 相対ベクトルを求める
	VECTOR v3SubAbs = VSub(player->m_rigidbody.GetPos(), ground->m_rigidbody.GetPos());
	v3SubAbs = VGet(abs(v3SubAbs.x), abs(v3SubAbs.y), abs(v3SubAbs.z));

	// 衝突距離を求める
	// 衝突距離はそれぞれの対応した辺の長さを足して2で割ったもの
	VECTOR v3AddScale = VScale(VAdd(player->m_rigidbody.GetScale(), ground->m_rigidbody.GetScale()), 0.5f);

	// 各成分の当たり判定
	bool isXHit = v3SubAbs.x < v3AddScale.x;
	bool isYHit = v3SubAbs.y < v3AddScale.y;
	bool isZHit = v3SubAbs.z < v3AddScale.z;

	if (isXHit && isYHit && isZHit)
	{
		return true;
	}
	else
	{
		return false;
	}

}
