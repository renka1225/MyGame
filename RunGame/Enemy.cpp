#include "Enemy.h"
#include "ManagerModel.h"
#include "Game/Game.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="pModel">3Dモデル</param>
Enemy::Enemy(std::shared_ptr<ManagerModel> pModel) :
	m_pModel(pModel),
	m_pos(VGet(0.0f, 0.0f, 0.0f)),
	m_isExist(false)
{
	m_modelHandle = MV1DuplicateModel(m_pModel->GetEnemyHandle());

	// 3Dモデルの縮小
	MV1SetScale(m_modelHandle, VGet(kScale, kScale, kScale));
	// 3DモデルをY軸方向に回転
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, kDirY, 0.0f));
}


/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{
	MV1DeleteModel(m_modelHandle);
}


/// <summary>
/// 初期化
/// </summary>
void Enemy::Init(VECTOR pos)
{
	m_pos = pos;
}

/// <summary>
/// 更新
/// </summary>
void Enemy::Update()
{
	//  敵の座標をスクリーン座標に変換する
	VECTOR screenPos = ConvWorldPosToScreenPos(m_pos);

	if (screenPos.x <= Game::kScreenWidth && screenPos.x >= 0)
	{
		m_isExist = true;
	}
	else
	{
		m_isExist = false;
	}

	// 画面内にいない敵の処理はしない
	if (!m_isExist) return;

	// 敵配置
	MV1SetPosition(m_modelHandle, m_pos);

	// TODO:横に移動させる
	//m_pos = VAdd(m_pos, VGet(kMove, 0.0f, 0.0f));
	
	// 当たり判定の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, m_pos.z, kWidth, kHeight);
}


/// <summary>
/// 描画
/// </summary>
void Enemy::Draw()
{
	if (!m_isExist) return;

	// ３Ｄモデルの描画
	MV1DrawModel(m_modelHandle);

#ifdef _DEBUG
	// MEMO:敵の当たり判定表示
	m_colRect.Draw(0xff00ff, false);
#endif

}


/// <summary>
/// 終了
/// </summary>
void Enemy::End()
{
}
