#include "DxLib.h"
#include "Collision3DBox.h"
#include <utility>

/// <summary>
/// コンストラクタ
/// </summary>
Collision3DBox::Collision3DBox():
	m_minPos(VGet(0.0f, 0.0f, 0.0f)),
	m_maxPos(VGet(0.0f, 0.0f, 0.0f)),
	m_centerPos(VGet(0.0f, 0.0f, 0.0f)),
	m_left(0.0f),
	m_bottom(0.0f),
	m_front(0.0f),
	m_right(0.0f),
	m_top(0.0f),
	m_back(0.0f)
{
}


/// <summary>
/// 描画
/// </summary>
/// <param name="color">当たり判定の色</param>
/// <param name="pos">モデルの座標</param>
/// <param name="size">モデルの当たり判定のサイズ</param>
void Collision3DBox::Draw(unsigned int color, VECTOR pos, VECTOR size)
{
	// 当たり判定を描画
	//左下手前から右下手前
	DrawLine3D(VGet(m_left, m_bottom, m_front), VGet(m_right, m_bottom, m_front), color);
	// 左下手前から左上手前
	DrawLine3D(VGet(m_left, m_bottom, m_front), VGet(m_left, m_top, m_front), color);
	// 左下手前から左下奥
	DrawLine3D(VGet(m_left, m_bottom, m_front), VGet(m_left, m_bottom, m_back), color);
	// 右上手前から右下手前
	DrawLine3D(VGet(m_right, m_top, m_front), VGet(m_right, m_bottom, m_front), color);
	// 右上手前から左上手前
	DrawLine3D(VGet(m_right, m_top, m_front), VGet(m_left, m_top, m_front), color);
	// 右上手前から右上奥
	DrawLine3D(VGet(m_right, m_top, m_front), VGet(m_right, m_top, m_back), color);
	// 左上奥から左上手前
	DrawLine3D(VGet(m_left, m_top, m_back), VGet(m_left, m_top, m_front), color);
	// 左上奥から左下奥
	DrawLine3D(VGet(m_left, m_top, m_back), VGet(m_left, m_bottom, m_back), color);
	// 左上奥から右上奥
	DrawLine3D(VGet(m_left, m_top, m_back), VGet(m_right, m_top, m_back), color);
	// 右下奥から左下奥
	DrawLine3D(VGet(m_right, m_bottom, m_back), VGet(m_right, m_bottom, m_back), color);
	// 右下奥から右下手前
	DrawLine3D(VGet(m_right, m_bottom, m_back), VGet(m_right, m_bottom, m_front), color);	
	// 右下奥から右上奥
	DrawLine3D(VGet(m_right, m_bottom, m_back), VGet(m_right, m_top, m_front), color);
}

/// <summary>
/// 中心点と幅高さ奥行を指定
/// </summary>
/// <param name="pos"></param>
/// <param name="size"></param>
void Collision3DBox::SetCenter(VECTOR pos, VECTOR size)
{
	m_left = pos.x - size.x * 0.5f;
	m_top = pos.y - size.y * 0.5f;
	m_front = pos.z - size.z * 0.5f;
	m_right = pos.x + size.x * 0.5f;
	m_top = pos.y + size.y * 0.5f;
	m_back = pos.z + size.z * 0.5f;
}

/// <summary>
/// バウディングボックスを作成する
/// </summary>
/// <param name="handle">モデルハンドル</param>
void Collision3DBox::CreateBoundingBox(int handle)
{
	// メッシュの数を取得
	auto meshNum = MV1GetMeshNum(handle);
	for (int i = 0; i < meshNum; i++)
	{
		VECTOR modelMinPos = MV1GetMeshMinPosition(handle, i);
		VECTOR modelMaxPos = MV1GetMeshMaxPosition(handle, i);

		m_minPos.x = std::min(m_minPos.x, modelMinPos.x);
		m_minPos.y = std::min(m_minPos.y, modelMinPos.y);
		m_minPos.z = std::min(m_minPos.z, modelMinPos.z);

		m_maxPos.x = std::max(m_maxPos.x, modelMaxPos.x);
		m_maxPos.y = std::max(m_maxPos.y, modelMaxPos.y);
		m_maxPos.z = std::max(m_maxPos.z, modelMaxPos.z);
	}
	m_centerPos = VScale(VAdd(m_minPos, m_maxPos), 0.5f);
}


/// <summary>
/// 直方体同士の当たり判定の処理
/// </summary>
/// <param name="col3DBox">判定を行う3Dモデル</param>
/// <returns>当たったか</returns>
bool Collision3DBox::IsCollision(const Collision3DBox& col3DBox)
{	
	//// 相対ベクトルを求める
	//VECTOR v3SubAbs = VSub(m_centerPos, col3DBox.m_centerPos);
	//v3SubAbs = VGet(abs(v3SubAbs.x), abs(v3SubAbs.y), abs(v3SubAbs.z));

	//// 衝突距離を求める
	//// 衝突距離はそれぞれの対応した辺の長さを足して2で割ったもの
	//VECTOR v3AddScale = VScale(VAdd((VGet(kScale, kScale, kScale), MV1GetScale(stage.GetStageHandle())), 0.5f);
	//// TODO;当たり判定の範囲を広げる(仮実装)
	//v3AddScale = VAdd(v3AddScale, VGet(0.0f, 20.0f, 0.0f));

	//// 各成分の当たり判定
	//bool isXHit = v3SubAbs.x < v3AddScale.x;
	//bool isYHit = v3SubAbs.y < v3AddScale.y;
	//bool isZHit = v3SubAbs.z < v3AddScale.z;

	//if (isXHit && isYHit && isZHit) return true;

	//return false;

	// 絶対に当たらないパターンをはじいていく
	if (m_left > col3DBox.m_right) return false;
	if (m_top > col3DBox.m_bottom) return false;
	if (m_front > col3DBox.m_back) return false;
	if (m_right < col3DBox.m_left) return false;
	if (m_bottom < col3DBox.m_top) return false;
	if (m_back < col3DBox.m_front) return false;

	// 当たらないパターン以外は当たっている
	return true;
}
